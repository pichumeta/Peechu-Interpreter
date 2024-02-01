//
// Created by Jamie on 24/01/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"

class Parser {
public:
    inline static constinit size_t max_arg_level = 500;
    inline static constinit size_t max_lines = 1000;

    explicit Parser(std::vector<Token *> tokens) noexcept;
    ~Parser() noexcept;

    [[nodiscard]] std::vector<std::vector<ParsedToken *>> parsed_tokens() const noexcept;

private:
    void Parse() noexcept;
    void Clean() noexcept;
    void ErrorCheck() noexcept;
    void ParseTokens() noexcept;
    void ReEvalTypes() noexcept;
    void RemoveWhitespace() noexcept;
    void ReorderLevel() noexcept;
    void ReorderPrecedence() noexcept;
    void Split() noexcept;

    std::vector<Token *> m_tokens;
    std::vector<std::vector<Token *>> m_split_tokens;
    std::vector<std::vector<ParsedToken *>> m_parsed_tokens;

};



#endif //PARSER_H
