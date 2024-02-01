//
// Created by Jamie on 25/01/2024.
//

#include "Loop.h"

Scope::Scope(std::vector<std::vector<ParsedToken *>> parsed_tokens, std::vector<std::shared_ptr<Scope>> functions,
        std::vector<std::shared_ptr<Variable>> variables) noexcept : m_parsed_tokens(std::move(parsed_tokens)),
                m_functions(std::move(functions)),
                m_variables(std::move(variables)) {

}

std::shared_ptr<Scope> Scope::FindFunction(const std::string &function_name) const noexcept {
    for (const auto &function : m_functions)
        if (function->get_name() == function_name)
            return function;

    return nullptr;
}

std::shared_ptr<Variable> Scope::FindVariable(const std::string &variable_name) const noexcept {
    for (const auto &variable : m_variables)
        if (variable->name() == variable_name)
            return variable;

    return nullptr;
}

std::pair<Any, ControlFlow> Scope::Run(const std::vector<std::shared_ptr<Any>> &args) noexcept {
    return operator()();
}

enum class ScopeType {
    Function,
    Loop,
    None,
    Scope
};

std::pair<Any, ControlFlow> Scope::operator()() noexcept {
    auto next_scope_type = ScopeType::None;
    std::vector<std::vector<ParsedToken *>> next_scope_tokens(Parser::max_lines);

    bool new_scope = false;
    bool if_ = true;

    size_t level = 0;

    std::string function_name;
    std::vector<std::string> param_names;

    auto RunNextScope = [&] {
        new_scope = false;

        std::pair result = {null_value, ControlFlow::None};

        switch (next_scope_type) {
            case ScopeType::Function: {
                auto function = std::make_shared<Function>(next_scope_tokens, m_functions, m_variables,
                    param_names, function_name);
                m_functions.emplace_back(function);
            } break;

            case ScopeType::Loop: {
                const auto loop = std::make_unique<Loop>(next_scope_tokens, m_functions, m_variables);
                result = loop->Run({});
            } break;

            case ScopeType::Scope: {
                if (!if_) break;

                const auto scope = std::make_unique<Scope>(next_scope_tokens, m_functions, m_variables);
                result = scope->Run({});
            } break;

            default: break;
        }

        next_scope_type = ScopeType::None;
        next_scope_tokens.clear();
        next_scope_tokens.reserve(Parser::max_lines);

        function_name.clear();
        param_names.clear();

        return result;
    };

    for (size_t i = 0; i < m_parsed_tokens.size(); i++) {
        const auto &tokens = m_parsed_tokens[i];
        if (tokens.empty()) continue;

        std::vector literals(Parser::max_arg_level,
            std::vector<std::vector<std::shared_ptr<Any>>>(Parser::max_arg_level));

        for (const auto &token : tokens) {
            if (new_scope) {
                if (token->type != semantics::tokens::TokenType::Literal &&
                    token->type != semantics::tokens::TokenType::Variable &&
                    token->type != semantics::tokens::TokenType::Function)
                    switch (semantics::tokens::tokens.at(token->str)) {
                    case semantics::tokens::Tokens::ScopeBegin: {
                        level++;
                    } break;

                    case semantics::tokens::Tokens::ScopeEnd: {
                        level--;

                        if (level == 0) {
                            next_scope_tokens[i].emplace_back(token);

                            if (const auto [value, control_flow] = RunNextScope();
                                control_flow != ControlFlow::None)
                                return {value, control_flow};

                            continue;
                        }

                    } break;

                    default: break;
                }

                next_scope_tokens[i].emplace_back(token);

                continue;
            }

            if (next_scope_type == ScopeType::Function) {
                if (token->type != semantics::tokens::TokenType::Variable &&
                    token->type != semantics::tokens::TokenType::Function)
                    goto check;

                if (token->level == 0 && function_name.empty()) {
                    function_name = token->str;
                    continue;
                }

                param_names.emplace_back(token->str);
                continue;
            }

        check:
            switch (token->type) {
                case semantics::tokens::TokenType::Keyword: {
                    const auto literals_ = literals[0][0];
                    const auto expression_result = literals_.empty() ?
                        null_value : **(literals_.end() - 1);

                    switch (semantics::tokens::keywords.at(token->str)) {
                        case semantics::tokens::Tokens::Break:
                            return {null_value, ControlFlow::Break};

                        case semantics::tokens::Tokens::Continue:
                            return {null_value, ControlFlow::Continue};

                        case semantics::tokens::Tokens::Else: {
                            if_ = !if_;
                        } break;

                        case semantics::tokens::Tokens::Function: {
                            next_scope_type = ScopeType::Function;
                        } break;

                        case semantics::tokens::Tokens::If: {
                            if_ = expression_result.ToBool();
                        } break;

                        case semantics::tokens::Tokens::Return:
                            return {expression_result, ControlFlow::Return};

                        case semantics::tokens::Tokens::VariableInitialiser: {
                            const ParsedToken *next_token = *(&token + 1);
                            auto variable = std::make_shared<Variable>(null_value.any(), next_token->str);
                            m_variables.emplace_back(variable);
                        } break;

                        default: break;
                    }
                } break;

                case semantics::tokens::TokenType::Function: {
                    std::vector<std::shared_ptr<Any>> args;
                    std::vector<std::vector<std::shared_ptr<Any>>> &arg_literals =
                        literals[token->level + 1];

                    auto &literals_ = literals[token->level][token->number];

                    for (const auto &vec : arg_literals)
                        args.insert(args.end(), vec.begin(), vec.end());

                    Any result;

                    if (const auto function = FindFunction(token->str)) {
                        result = function->Run(args).first;
                        literals_.emplace_back(std::make_shared<Any>(result));

                        for (auto &vec : arg_literals)
                            vec.clear();

                        break;
                    }

                    if (!inbuilt::functions.contains(token->str))
                        error::Throw(error::Error::Undefined,
                            std::format("undefined function: {}", token->str));

                    auto function = inbuilt::functions.at(token->str);
                    result = function(args);

                    literals_.emplace_back(std::make_shared<Any>(result));

                    for (auto &vec : arg_literals)
                        vec.clear();

                } break;

                case semantics::tokens::TokenType::Literal: {
                    literals[token->level][token->number].emplace_back(std::make_shared<Any>(token->str));
                } break;

                // let foo = !bar(1 + 3 + baz(4 * baz(9) + 2)
                // let foo bar ! =

                // let foo = baz + 4 * bar
                // let foo baz 4 bar * + =
                // null 1 4 2 * + =
                // null 1 8 + =
                // null 9 =
                //

                case semantics::tokens::TokenType::LogicalUnaryOperator:
                case semantics::tokens::TokenType::MathsUnaryOperator: {
                    auto &unary_operator = inbuilt::logical_unary_operators.contains(token->str) ?
                        inbuilt::logical_unary_operators.at(token->str) : inbuilt::maths_unary_operators.at(token->str);

                    auto &literals_ = literals[token->level][token->number];
                    auto &operand = *(literals_.end() - 1);
                    auto result = unary_operator(*operand);
                    *operand = result;
                } break;

                case semantics::tokens::TokenType::MathsOperator:
                case semantics::tokens::TokenType::ComparisonOperator:
                case semantics::tokens::TokenType::BitwiseOperator:
                case semantics::tokens::TokenType::LogicalOperator:
                case semantics::tokens::TokenType::AssignmentOperator: {
                    std::function<Any(const Any &, const Any &)> operator_;

                    switch (token->type) {
                        case semantics::tokens::TokenType::MathsOperator:
                            operator_ = inbuilt::maths_operators.at(token->str);
                            break;

                        case semantics::tokens::TokenType::ComparisonOperator:
                            operator_ = inbuilt::comparison_operators.at(token->str);
                            break;

                        case semantics::tokens::TokenType::BitwiseOperator:
                            operator_ = inbuilt::bitwise_operators.at(token->str);
                            break;

                        case semantics::tokens::TokenType::LogicalOperator:
                            operator_ = inbuilt::logical_operators.at(token->str);
                            break;

                        case semantics::tokens::TokenType::AssignmentOperator:
                            operator_ = inbuilt::assignment_operators.at(token->str);
                            break;

                        default: break;
                    }

                    auto &literals_ = literals[token->level][token->number];

                    if (literals_.size() < 2)
                        error::Throw(error::Error::Argument,
                            std::format("operation: {} expected 2 operands", token->str));

                    const auto left = *(literals_.end() - 2);
                    const auto right = *(literals_.end() - 1);

                    auto result = operator_(*left, *right);

                    literals_.pop_back();
                    literals_.pop_back();

                    literals_.emplace_back(std::make_shared<Any>(result));

                } break;

                case semantics::tokens::TokenType::Separator: {
                    switch (semantics::tokens::tokens.at(token->str)) {
                        case semantics::tokens::Tokens::ScopeBegin: {
                            new_scope = true;
                            level = 1;
                        } break;

                        case semantics::tokens::Tokens::ScopeEnd:
                            return {null_value, ControlFlow::None};

                        default: break;
                    }
                } break;

                case semantics::tokens::TokenType::Variable: {
                    if (const auto variable = FindVariable(token->str)) {
                        literals[token->level][token->number].emplace_back(variable);
                        break;
                    }

                    error::Throw(error::Error::Undefined,
                            std::format("undefined variable: {}", token->str));
                } break;

                default: break;
            }
        }
    }

    return {null_value, ControlFlow::None};
}
