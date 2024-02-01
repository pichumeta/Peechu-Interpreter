//
// Created by Jamie on 01/02/2024.
//

#ifndef LOOP_H
#define LOOP_H

#include "Function.h"

class Loop final : public Scope {
public:
    explicit Loop(std::vector<std::vector<ParsedToken *>> parsed_tokens, std::vector<std::shared_ptr<Scope>> functions,
        std::vector<std::shared_ptr<Variable>> variables) noexcept;

    std::pair<Any, ControlFlow> Run(const std::vector<std::shared_ptr<Any>> &args) noexcept override;

};



#endif //LOOP_H
