//
// Created by Jamie on 24/01/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser {
public:
    explicit Parser(std::vector<Token *> &&tokens) noexcept;
    ~Parser() noexcept;

private:
    inline static constinit size_t max_arg_level = 500;
    inline static constinit size_t max_lines = 1000;

    void Parse() noexcept;
    void Clean() noexcept;
    void ErrorCheck() noexcept;
    void ParseTokens() noexcept;
    void ReEvalTypes() noexcept;
    void RemoveWhitespace() noexcept;
    void Split() noexcept;

    std::vector<Token *> m_tokens;
    std::vector<std::vector<Token *>> m_split_tokens;
    std::vector<std::vector<ParsedToken *>> m_parsed_tokens;

};



#endif //PARSER_H
