//
// Created by Jamie on 25/01/2024.
//

#ifndef SCOPE_H
#define SCOPE_H

#include "Parser.h"

class Scope {
public:
    explicit Scope(std::vector<std::vector<ParsedToken *>> parsed_tokens, std::vector<std::shared_ptr<Scope>> functions,
        std::vector<std::shared_ptr<Variable>> variables) noexcept;
    virtual ~Scope() noexcept = default;

    std::pair<Any, ControlFlow> operator()() noexcept;

    virtual std::pair<Any, ControlFlow> Run(const std::vector<std::shared_ptr<Any>> &args) noexcept;

    [[nodiscard]] virtual std::string get_name() const noexcept { return ""; }

protected:
    [[nodiscard]] std::shared_ptr<Scope> FindFunction(const std::string &function_name) const noexcept;
    [[nodiscard]] std::shared_ptr<Variable> FindVariable(const std::string &variable_name) const noexcept;

    std::vector<std::vector<ParsedToken *>> m_parsed_tokens;

    std::vector<std::shared_ptr<Scope>> m_functions;
    std::vector<std::shared_ptr<Variable>> m_variables;

};



#endif //SCOPE_H
