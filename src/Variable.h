//
// Created by Jamie on 20/01/2024.
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include "semantics/Types.h"

class Variable : public Any {
public:
    explicit Variable(const std::any &any, std::string name) noexcept;

    [[nodiscard]] std::string name() const noexcept;
    void set_name(const std::string &name) noexcept;

    [[nodiscard]] bool pass_by_ref() const noexcept;
    void set_pass_by_ref(bool pass_by_ref) noexcept;

private:
    std::string m_name;
    bool m_pass_by_ref = false;

};



#endif //VARIABLE_H
