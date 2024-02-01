//
// Created by Jamie on 20/01/2024.
//

#include "Variable.h"

Variable::Variable(const std::any &any, std::string name) noexcept : Any(any), m_name(std::move(name)) {

}

std::string Variable::name() const noexcept {
    return m_name;
}

void Variable::set_name(const std::string &name) noexcept {
    m_name = name;
}

bool Variable::pass_by_ref() const noexcept {
    return m_pass_by_ref;
}

void Variable::set_pass_by_ref(const bool pass_by_ref) noexcept {
    m_pass_by_ref = pass_by_ref;
}
