//
// Created by Jamie on 25/01/2024.
//

#include "Function.h"

Scope::Scope(std::vector<std::vector<ParsedToken *>> &&parsed_tokens, std::vector<Scope *> &&functions,
        std::vector<Variable *> &variables) noexcept : m_parsed_tokens(parsed_tokens),
                m_functions(functions),
                m_variables(variables) {

}

void Scope::Run() noexcept {
    for (const auto &tokens : m_parsed_tokens) {
        for (const auto &token : tokens) {

        }
    }
}
