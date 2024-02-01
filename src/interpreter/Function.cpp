//
// Created by Jamie on 25/01/2024.
//

#include "Loop.h"

Function::Function(std::vector<std::vector<ParsedToken *>> parsed_tokens,
    std::vector<std::shared_ptr<Scope>> functions,
    std::vector<std::shared_ptr<Variable>> variables,
    std::vector<std::string> param_names,
    std::string name) noexcept :
    Scope(std::move(parsed_tokens), std::move(functions), std::move(variables)),
    m_params_names(std::move(param_names)), m_name(std::move(name)) {

}

std::pair<Any, ControlFlow> Function::Run(const std::vector<std::shared_ptr<Any>> &args) noexcept {
    if (args.size() != m_params_names.size())
        error::Throw(error::Error::Argument,
            std::format("function: {} expected {} args", m_name, m_params_names.size()));

    for (size_t i = 0; i < args.size(); i++) {
        auto &arg = args[i];

        if (arg->pass_by_ref()) {
            arg->set_name(m_params_names[i]);
            m_variables.emplace_back(reinterpret_cast<Variable *>(arg.get()));
            continue;
        }

        auto variable = std::make_shared<Variable>(arg->any(), m_params_names[i]);
        m_variables.emplace_back(variable);
    }

    auto [res, _] = operator()();
    m_variables.clear();

    return {res, ControlFlow::Return};
}

std::string Function::get_name() const noexcept {
    return m_name;
}
