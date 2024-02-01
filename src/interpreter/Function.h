//
// Created by Jamie on 25/01/2024.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include "Scope.h"

class Function final : public Scope {
public:
    explicit Function(std::vector<std::vector<ParsedToken *>> parsed_tokens, std::vector<std::shared_ptr<Scope>> functions,
        std::vector<std::shared_ptr<Variable>> variables, std::vector<std::string> param_names, std::string name) noexcept;

    std::pair<Any, ControlFlow> Run(const std::vector<std::shared_ptr<Any>> &args) noexcept override;

    [[nodiscard]] std::string get_name() const noexcept override;

protected:
    std::vector<std::string> m_params_names;
    std::string m_name;

};



#endif //FUNCTION_H
