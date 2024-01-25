//
// Created by Jamie on 20/01/2024.
//

#ifndef TOKEN_H
#define TOKEN_H

#include "../Inbuilt.h"

struct Token {
    using TokenType = semantics::tokens::TokenType;
    std::string str;
    TokenType type = TokenType::Literal;
};

struct ParsedToken : Token {
    size_t level = 0;
    size_t number = 0;
};

#endif //TOKEN_H
