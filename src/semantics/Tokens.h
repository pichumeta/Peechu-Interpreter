//
// Created by Jamie on 19/01/2024.
//

#ifndef TOKENS_H
#define TOKENS_H

#include <ranges>
#include <unordered_map>

#include "../utils/Utils.h"

namespace semantics::tokens {
    constexpr int first = -1;
    constexpr int pre_expression = 0;
    constexpr int post_expression = 100;
    constexpr int literal = 10;
    constexpr int identifier = literal;
    constexpr int unary_op = 30;
    constexpr int maths_op = 40;
    constexpr int comparison_op = 50;
    constexpr int bitwise_op = 60;
    constexpr int logical_op = 70;
    constexpr int assignment_op = 80;

    enum class Tokens {
        // Whitespace:
        Flush = first,
        Space = first,

        // Line separators:
        NewLine = first,

        // Keywords:
        Else = post_expression + 9,
        Function = pre_expression + 8,
        If = post_expression + 7,
        Loop = post_expression + 6,
        PassByReference = pre_expression + 5,
        Return = post_expression + 4,
        Break = post_expression + 2,
        Continue = post_expression + 3,
        VariableInitialiser = pre_expression + 1,

        // Identifiers
        FunctionName = identifier,
        VariableName = identifier,

        //
        // FunctionCall,
        // MemberAccess,

        // Maths unary operators:
        Decrement = unary_op,
        Increment = unary_op,

        // Logical unary operators:
        Not = unary_op,

        // Maths operators (left to right):
        Division = maths_op,
        Multiplication = maths_op,
        Remainder = maths_op,

        Addition = maths_op + 5,
        Subtraction = maths_op + 5,

        // Comparison operators (left to right):
        // (relational)
        GreaterThan = comparison_op,
        GreaterThanOrEqualTo = comparison_op,
        LessThan = comparison_op, // I usually prefer to say lower than or smaller than
        LessThanOrEqualTo = comparison_op,
        // (equality)
        EqualTo = comparison_op,
        NotEqualTo = comparison_op,

        // Bitwise operators (left to right):
        BitwiseAnd = bitwise_op,
        BitwiseOr = bitwise_op + 5,

        // Logical operators (left to right):
        LogicalAnd = logical_op,
        LogicalOr = logical_op + 5,

        // Assigment operators
        DirectAssigment = assignment_op,
        SumAssignment = assignment_op,
        DifferenceAssignment = assignment_op,
        ProductAssignment = assignment_op,
        DivisionAssginment = assignment_op,
        RemainderAssignment = assignment_op,

        // Separators:
        Comma = first,
        OpenBracket = first,
        ClosedBracket = first,
        ScopeBegin = post_expression + 10,
        ScopeEnd = post_expression + 11,
    };

    enum class TokenType {
        Any,
        None,

        Literal,

        Keyword,

        Identifier,

        Variable,
        Function,

        MathsUnaryOperator,
        LogicalUnaryOperator,

        MathsOperator,
        ComparisonOperator,

        BitwiseOperator,
        LogicalOperator,

        AssignmentOperator,

        LineSeparator,
        Separator,
        Whitespace
    };

    inline const std::string literal_chars = "[\"";

    inline const std::string else_str = "else";
    inline const std::string function_str = "fun";
    inline const std::string if_str = "if";
    inline const std::string loop_str = "loop";
    inline const std::string break_str = "break";
    inline const std::string continue_str = "continue";
    inline const std::string pass_by_reference_str = "ref";
    inline const std::string return_str = "return";
    inline const std::string variable_initialiser_str = "let";

    inline const std::string function_call_str = " ()";
    inline const std::string member_access_str = ".";

    inline const std::string decrement_str = "--";
    inline const std::string increment_str = "++";

    inline const std::string not_str = "!";

    inline const std::string division_str = "/";
    inline const std::string multiplication_str = "*";
    inline const std::string remainder_str = "%";
    inline const std::string addition_str = "+";
    inline const std::string substraction_str = "-";

    inline const std::string greater_than_str = ">";
    inline const std::string greater_than_or_equal_to_str = ">=";
    inline const std::string less_than_str = "<";
    inline const std::string less_than_or_equal_to_str = "<=";
    inline const std::string equal_to_str = "==";
    inline const std::string not_equal_to_str = "!=";

    inline const std::string bitwise_and_str = "&";
    inline const std::string bitwise_or_str = "|";

    inline const std::string logical_and_str = "&&";
    inline const std::string logical_or_str = "||";

    inline const std::string direct_assignment_str = "=";
    inline const std::string sum_assignment_str = "+=";
    inline const std::string differnce_assignment_str = "-=";
    inline const std::string product_assignment_str = "*=";
    inline const std::string division_assignment_str = "/=";
    inline const std::string remainder_assignment_str = "%=";

    inline const std::string new_line_str = "\n";

    inline const std::string comma_str = ",";
    inline const std::string open_bracket_str = "(";
    inline const std::string closed_bracket_str = ")";
    inline const std::string scope_begin_str = "{";
    inline const std::string scope_end_str = "}";

    inline const std::string flush_str = "\r";
    inline const std::string space_str = " ";

    inline const std::unordered_map<std::string, Tokens> keywords {
        {else_str, Tokens::Else},
        {function_str, Tokens::Function},
        {if_str, Tokens::If},
        {loop_str, Tokens::Loop},
        {break_str, Tokens::Break},
        {continue_str, Tokens::Continue},
        {pass_by_reference_str, Tokens::PassByReference},
        {return_str, Tokens::Return},
        {variable_initialiser_str, Tokens::VariableInitialiser}
    };

    inline const auto keyword_keys = keywords | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> maths_unary_operators {
        {decrement_str, Tokens::Decrement},
        {increment_str, Tokens::Increment}
    };

    inline const auto maths_unary_operators_keys = maths_unary_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> logical_unary_operators {
        {not_str, Tokens::Not}
    };

    inline const auto logical_unary_operators_keys = logical_unary_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> maths_operators {
        {division_str, Tokens::Division},
        {multiplication_str, Tokens::Multiplication},
        {remainder_str, Tokens::Remainder},

        {addition_str, Tokens::Addition},
        {substraction_str, Tokens::Subtraction}
    };

    inline const auto maths_operators_keys = maths_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> comparison_operators {
        {greater_than_str, Tokens::GreaterThan},
        {greater_than_or_equal_to_str, Tokens::GreaterThanOrEqualTo},
        {less_than_str, Tokens::LessThan},
        {less_than_or_equal_to_str, Tokens::LessThanOrEqualTo},

        {equal_to_str, Tokens::EqualTo},
        {not_equal_to_str, Tokens::NotEqualTo}
    };

    inline const auto comparison_operators_keys = comparison_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> bitwise_operators {
        {bitwise_and_str, Tokens::BitwiseAnd},
        {bitwise_or_str, Tokens::BitwiseOr}
    };

    inline const auto bitwise_operators_keys = bitwise_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> logical_operators {
        {logical_and_str, Tokens::LogicalAnd},
        {logical_or_str, Tokens::LogicalOr}
    };

    inline const auto logical_operators_keys = logical_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> assignment_operators {
        {direct_assignment_str, Tokens::DirectAssigment},
        {sum_assignment_str, Tokens::SumAssignment},
        {differnce_assignment_str, Tokens::DifferenceAssignment},
        {product_assignment_str, Tokens::ProductAssignment},
        {division_assignment_str, Tokens::DivisionAssginment},
        {remainder_assignment_str, Tokens::RemainderAssignment}
    };

    inline const auto assignment_operators_keys = assignment_operators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> line_separators {
        {new_line_str, Tokens::NewLine}
    };

    inline const auto line_separators_keys = line_separators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> separators {
        {comma_str, Tokens::Comma},
        {open_bracket_str, Tokens::OpenBracket},
        {closed_bracket_str, Tokens::ClosedBracket},
        {scope_begin_str, Tokens::ScopeBegin},
        {scope_end_str, Tokens::ScopeEnd}
    };

    inline const auto separators_keys = separators | std::views::keys;

    inline const std::unordered_map<std::string, Tokens> whitespace {
        {flush_str, Tokens::Flush},
        {space_str, Tokens::Space}
    };

    inline const auto whitespace_keys = whitespace | std::views::keys;

    inline const std::unordered_map<TokenType, std::vector<std::string>> token_types {
        //{TokenType::Keyword, std::vector(keyword_keys.begin(), keyword_keys.end())},
        {TokenType::MathsUnaryOperator, std::vector(maths_unary_operators_keys.begin(), maths_unary_operators_keys.end())},
        {TokenType::LogicalUnaryOperator, std::vector(logical_unary_operators_keys.begin(), logical_unary_operators_keys.end())},
        {TokenType::MathsOperator, std::vector(maths_operators_keys.begin(), maths_operators_keys.end())},
        {TokenType::ComparisonOperator, std::vector(comparison_operators_keys.begin(), comparison_operators_keys.end())},
        {TokenType::BitwiseOperator, std::vector(bitwise_operators_keys.begin(), bitwise_operators_keys.end())},
        {TokenType::LogicalOperator, std::vector(logical_operators_keys.begin(), logical_operators_keys.end())},
        {TokenType::LineSeparator, std::vector(line_separators_keys.begin(), line_separators_keys.end())},
        {TokenType::AssignmentOperator, std::vector(assignment_operators_keys.begin(), assignment_operators_keys.end())},
        {TokenType::Separator, std::vector(separators_keys.begin(), separators_keys.end())},
        {TokenType::Whitespace, std::vector(whitespace_keys.begin(), whitespace_keys.end())},
    };

    inline const std::unordered_map<TokenType, std::vector<TokenType>> expects {
        {TokenType::Literal, {TokenType::MathsUnaryOperator, TokenType::LogicalUnaryOperator, TokenType::MathsOperator,
                TokenType::ComparisonOperator, TokenType::BitwiseOperator, TokenType::LogicalOperator, TokenType::Separator, TokenType::LineSeparator}},
        {TokenType::Keyword, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::Variable, {TokenType::MathsOperator, TokenType::ComparisonOperator, TokenType::LogicalOperator,
            TokenType::BitwiseOperator, TokenType::AssignmentOperator, TokenType::Separator, TokenType::LineSeparator}},
        {TokenType::Function, {TokenType::Separator, TokenType::LineSeparator}},
        {TokenType::LogicalUnaryOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::MathsUnaryOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::MathsOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::ComparisonOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::BitwiseOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::LogicalOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::AssignmentOperator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::LineSeparator}},
        {TokenType::Separator, {TokenType::Literal, TokenType::Variable, TokenType::Function, TokenType::MathsOperator,
            TokenType::ComparisonOperator, TokenType::BitwiseOperator, TokenType::LogicalOperator, TokenType::AssignmentOperator, TokenType::LineSeparator}}
    };

    inline const std::unordered_map<std::string, Tokens> tokens {
        {else_str, Tokens::Else},
        {function_str, Tokens::Function},
        {if_str, Tokens::If},
        {loop_str, Tokens::Loop},
        {break_str, Tokens::Break},
        {continue_str, Tokens::Continue},
        {pass_by_reference_str, Tokens::PassByReference},
        {return_str, Tokens::Return},
        {variable_initialiser_str, Tokens::VariableInitialiser},

        {decrement_str, Tokens::Decrement},
        {increment_str, Tokens::Increment},

        {not_str, Tokens::Not},

        {division_str, Tokens::Division},
        {multiplication_str, Tokens::Multiplication},
        {remainder_str, Tokens::Remainder},

        {addition_str, Tokens::Addition},
        {substraction_str, Tokens::Subtraction},

        {greater_than_str, Tokens::GreaterThan},
        {greater_than_or_equal_to_str, Tokens::GreaterThanOrEqualTo},
        {less_than_str, Tokens::LessThan},
        {less_than_or_equal_to_str, Tokens::LessThanOrEqualTo},

        {equal_to_str, Tokens::EqualTo},
        {not_equal_to_str, Tokens::NotEqualTo},

        {bitwise_and_str, Tokens::BitwiseAnd},
        {bitwise_or_str, Tokens::BitwiseOr},

        {logical_and_str, Tokens::LogicalAnd},
        {logical_or_str, Tokens::LogicalOr},

        {direct_assignment_str, Tokens::DirectAssigment},
        {sum_assignment_str, Tokens::SumAssignment},
        {differnce_assignment_str, Tokens::DifferenceAssignment},
        {product_assignment_str, Tokens::ProductAssignment},
        {division_assignment_str, Tokens::DivisionAssginment},
        {remainder_assignment_str, Tokens::RemainderAssignment},

        {new_line_str, Tokens::NewLine},

        {comma_str, Tokens::Comma},
        {open_bracket_str, Tokens::OpenBracket},
        {closed_bracket_str, Tokens::ClosedBracket},
        {scope_begin_str, Tokens::ScopeBegin},
        {scope_end_str, Tokens::ScopeEnd},

        {flush_str, Tokens::Flush},
        {space_str, Tokens::Space}
    };
}
#endif //TOKENS_H
