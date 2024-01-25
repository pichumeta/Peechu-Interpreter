//
// Created by Jamie on 24/01/2024.
//

#include "Parser.h"

Parser::Parser(std::vector<Token *> &&tokens) noexcept :
    m_tokens(std::move(tokens)), m_split_tokens(max_lines), m_parsed_tokens(max_lines) {
    Parse();
}

Parser::~Parser() noexcept {
    for (const auto &tokens : m_parsed_tokens)
        for (const auto &token : tokens)
            delete token;
}


void Parser::Parse() noexcept {
    RemoveWhitespace();
    ReEvalTypes();
    ErrorCheck();
    Split();
    ParseTokens();
    Clean();
}

void Parser::Clean() noexcept {
    m_parsed_tokens | std::views::filter([](const std::vector<ParsedToken *> &line) {
        return !line.empty();
    });
}

void Parser::ErrorCheck() noexcept {
    for (auto it = m_tokens.begin(); it < m_tokens.end() - 1; ++it) {
        const auto &token = *it;
        const auto &next_token = *(it + 1);

        if (!semantics::tokens::expects.contains(token->type))
            continue;

        if (const std::vector<semantics::tokens::TokenType> &expected = semantics::tokens::expects.at(token->type);
            std::ranges::find(expected, next_token->type) == expected.end())
            Throw(error::Error::Syntax, std::format("unexpected token: {}, after token: {}", next_token->str, token->str));
    }
}

void Parser::ParseTokens() noexcept {
    for (const auto &[tokens, parsed_tokens] : std::views::zip(m_split_tokens, m_parsed_tokens) /* std::views::zip()*/) {
        size_t level = 0;
        size_t number = 0;

        for (const auto &token : tokens) {
            if (token->str == semantics::tokens::open_bracket_str) {
                level++;
                continue;
            }

            if (token->str == semantics::tokens::closed_bracket_str) {
                level--;
                number = 0;
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
        switch (const auto &token = *it; token->type) {
            case semantics::tokens::TokenType::Whitespace: {
                m_tokens.erase(it);
            } break;

            default: break;
        }
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