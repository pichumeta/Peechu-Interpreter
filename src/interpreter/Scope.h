//
// Created by Jamie on 25/01/2024.
//

#ifndef SCOPE_H
#define SCOPE_H

#include "Parser.h"

class Scope {
public:
    explicit Scope(std::vector<std::vector<ParsedToken *>> &&parsed_tokens, std::vector<Scope *> &&functions,
        std::vector<Variable *> &variables) noexcept;

    virtual Any Call(const std::vector<Any &> args) noexcept { return null_value; }
    void Run() noexcept;

protected:
    std::vector<std::vector<ParsedToken *>> m_parsed_tokens;

    std::vector<Scope *> m_functions;
    std::vector<Variable *> &m_variables;

};



#endif //SCOPE_H
