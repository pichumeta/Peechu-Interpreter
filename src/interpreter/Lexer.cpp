//
// Created by Jamie on 22/01/2024.
//

#include "Lexer.h"

Lexer::Lexer(std::string &&text) noexcept : m_text(std::move(text)) {
    LoadTokens();
}

Lexer::~Lexer() noexcept {
    for (const auto &token : m_tokens)
        delete token;
}

std::vector<Token *> Lexer::tokens() const noexcept {
    return m_tokens;
}

void Lexer::LoadTokens() noexcept {
    while (Token *token = GetToken())
        m_tokens.emplace_back(token);
}

Token *Lexer::GetToken() noexcept {
    if (m_text.empty()) return nullptr;

    std::string token_string;
    auto token_type = semantics::tokens::TokenType::Identifier;

    for (const auto &c : m_text) {
        token_string += c;

        if (bool _break, _continue = false; std::ranges::any_of(semantics::tokens::literal_chars,
        [&](const char literal) {
            const size_t occurence_number =
                std::ranges::count(token_string, literal);

            if (occurence_number <= 0) return false;

            token_type = semantics::tokens::TokenType::Literal;

            _break = occurence_number == 2;
            _continue = token_string[0] == literal;

            return true;
        })) {
            if (_break) break;
            if (_continue) continue;
        }

        const size_t token_length = token_string.length();

        for (const auto &[_token_type, tokens] : semantics::tokens::token_types) {
            for (const auto &token : tokens) {
                if (token_string == token) {
                    token_type = _token_type;
                    continue;
                }

                const size_t _token_length = token.length();
                const size_t length_diff = token_length - _token_length;

                if (length_diff == 0 || _token_length >= token_length)
                    continue;

                if (token_string.substr(0, _token_length) == token) {
                    token_string.erase(_token_length, length_diff);
                    token_type = _token_type;
                    goto end;
                }

                if (token_string.substr(length_diff, _token_length) == token) {
                    token_string.erase(length_diff, _token_length);
                    goto end;
                }
            }
        }

//_continue:
    }

end:
    if (std::ranges::find(semantics::tokens::keyword_keys, token_string) != semantics::tokens::keyword_keys.end())
        token_type = semantics::tokens::TokenType::Keyword;

    if (Any::IsLiteral(token_string))
        token_type = semantics::tokens::TokenType::Literal;

    m_text.erase(0, token_string.length());
    return new Token(token_string, token_type);
}