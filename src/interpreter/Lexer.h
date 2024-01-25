//
// Created by Jamie on 22/01/2024.
//

#ifndef LEXER_H
#define LEXER_H

#include <algorithm>

#include "Token.h"

class Lexer {
public:
    explicit Lexer(std::string &&text) noexcept;
    ~Lexer() noexcept;

    [[nodiscard]] std::vector<Token *> tokens() const noexcept;

private:
    void LoadTokens() noexcept;
    Token *GetToken() noexcept;

    std::string m_text;
    std::vector<Token *> m_tokens;

};



#endif //LEXER_H
