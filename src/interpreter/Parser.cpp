//
// Created by Jamie on 24/01/2024.
//

#include "Parser.h"

Parser::Parser(std::vector<Token *> tokens) noexcept :
    m_tokens(std::move(tokens)), m_split_tokens(max_lines), m_parsed_tokens(max_lines) {
    Parse();
}

Parser::~Parser() noexcept {
    for (const auto &tokens : m_parsed_tokens)
        for (const auto &token : tokens)
            delete token;
}

std::vector<std::vector<ParsedToken *> > Parser::parsed_tokens() const noexcept {
    return m_parsed_tokens;
}

void Parser::Parse() noexcept {
    RemoveWhitespace();
    ReEvalTypes();
    Split();
    ParseTokens();
    Clean();
    ReorderLevel();
    ReorderPrecedence();
}

void Parser::Clean() noexcept {
    std::vector<std::vector<ParsedToken *>> new_parsed_tokens;

    for (const auto &parsed_tokens : m_parsed_tokens) {
        if (parsed_tokens.empty()) continue;
        new_parsed_tokens.emplace_back(parsed_tokens);
    }

    m_parsed_tokens = new_parsed_tokens;
}

void Parser::ErrorCheck() noexcept {
    for (auto it = m_tokens.begin(); it < m_tokens.end() - 1; ++it) {
        const auto &token = *it;
        const auto &next_token = *(it + 1);

        if (!semantics::tokens::expects.contains(token->type))
            continue;

        if (const std::vector<semantics::tokens::TokenType> &expected = semantics::tokens::expects.at(token->type);
            std::ranges::find(expected, next_token->type) == expected.end())
            Throw(error::Error::Syntax,
                std::format("unexpected token: {}, after token: {}", next_token->str, token->str));
    }
}

void Parser::ParseTokens() noexcept {
    for (const auto &[tokens, parsed_tokens] : std::views::zip(m_split_tokens, m_parsed_tokens) /* std::views::zip()*/) {
        size_t level = 0;
        std::vector<size_t> prev_numbers;
        size_t number = 0;

        for (const auto &token : tokens) {
            if (token->type == semantics::tokens::TokenType::Whitespace)
                continue;

            if (token->str == semantics::tokens::open_bracket_str) {
                level++;
                prev_numbers.emplace_back(number);
                number = 0;
                continue;
            }
            // let m = log(2, 3 + log(3, log(9) + 8) + 5
            if (token->str == semantics::tokens::closed_bracket_str) {
                level--;
                number = *(prev_numbers.end() - 1);
                prev_numbers.pop_back();
                continue;
            }

            if (token->str == semantics::tokens::comma_str) {
                number++;
                continue;
            }

            auto parsed_token = new ParsedToken{token->str, token->type, level, number};
            parsed_tokens.emplace_back(parsed_token);
        }
    }
}

void Parser::ReEvalTypes() noexcept {
    for (auto it = m_tokens.begin(); it < m_tokens.end(); ++it) {
        switch (const auto &token = *it; token->type) {
            case semantics::tokens::TokenType::Identifier: {
                token->type = semantics::tokens::TokenType::Variable;

                const auto next = it + 1;
                if (next == m_tokens.end())
                    break;

                if ((*next)->str == semantics::tokens::open_bracket_str)
                    token->type = semantics::tokens::TokenType::Function;

            } break;

            default: break;
        }
    }
}

void Parser::RemoveWhitespace() noexcept {
    for (auto it = m_tokens.begin(); it < m_tokens.end(); ++it) {
        if (const auto &token = *it;
            token->str.contains(' '))
            m_tokens.erase(it);
    }
}

void Parser::ReorderLevel() noexcept {
    for (auto &parsed_tokens : m_parsed_tokens) {
        size_t highest_level = 0;
        std::vector<std::vector<ParsedToken *>> reordered(max_arg_level);

        for (const auto &parsed_token : parsed_tokens) {
            reordered[parsed_token->level].emplace_back(parsed_token);
            highest_level = parsed_token->level > highest_level ? parsed_token->level : highest_level;
        }

        parsed_tokens.clear();
        for (int level = static_cast<int>(highest_level); level > -1; level--)
            parsed_tokens.insert(parsed_tokens.end(),
                reordered[level].begin(), reordered[level].end());
    }
}

void Parser::ReorderPrecedence() noexcept {
    for (auto &parsed_tokens : m_parsed_tokens) {
        auto Reorder = [](std::vector<ParsedToken *> &parsed_tokens_) {
            std::vector<std::vector<ParsedToken *>> new_parsed_tokens(max_arg_level);

            for (const auto &parsed_token : parsed_tokens_) {
                const auto precedence = parsed_token->type == semantics::tokens::TokenType::Variable ||
                    parsed_token->type == semantics::tokens::TokenType::Function ||
                    parsed_token->type == semantics::tokens::TokenType::Literal ?
                    semantics::tokens::identifier : static_cast<int>(semantics::tokens::tokens.at(parsed_token->str));

                new_parsed_tokens[precedence].emplace_back(parsed_token);
            }

            parsed_tokens_.clear();

            for (const auto &tokens : new_parsed_tokens) {
                if (tokens.empty()) continue;
                parsed_tokens_.insert(parsed_tokens_.end(), tokens.begin(), tokens.end());
            }
        };

        std::vector<ParsedToken *> new_parsed_tokens;
        std::vector<ParsedToken *> parsed_tokens_;

        size_t prev_level = parsed_tokens[0]->level;
        size_t prev_number = parsed_tokens[0]->number;

        for (const auto &parsed_token : parsed_tokens) {
            if (parsed_token->level != prev_level || parsed_token->number != prev_number) {
                Reorder(parsed_tokens_);
                new_parsed_tokens.insert(new_parsed_tokens.end(),
                    parsed_tokens_.begin(), parsed_tokens_.end());

                parsed_tokens_.clear();
            }

            parsed_tokens_.emplace_back(parsed_token);

            prev_level = parsed_token->level;
            prev_number = parsed_token->number;
        }

        Reorder(parsed_tokens_);
        new_parsed_tokens.insert(new_parsed_tokens.end(),
            parsed_tokens_.begin(), parsed_tokens_.end());

        parsed_tokens = new_parsed_tokens;
    }
}

void Parser::Split() noexcept {
    size_t line = 0;

    for (const auto &token : m_tokens) {
        if (token->type != semantics::tokens::TokenType::LineSeparator) {
            m_split_tokens[line].emplace_back(token);
            continue;
        }

        line++;
    }
}