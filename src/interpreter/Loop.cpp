//
// Created by Jamie on 01/02/2024.
//

#include "Loop.h"

Loop::Loop(std::vector<std::vector<ParsedToken *>> parsed_tokens,
    std::vector<std::shared_ptr<Scope>> functions,
    std::vector<std::shared_ptr<Variable>> variables) noexcept :
    Scope(std::move(parsed_tokens), std::move(functions), std::move(variables)) {

}


std::pair<Any, ControlFlow> Loop::Run(const std::vector<std::shared_ptr<Any>> &args) noexcept {
    auto [res, control_flow] = operator()();

    switch (control_flow) {
        case ControlFlow::Break: {
            control_flow = ControlFlow::None;
        } break;

        case ControlFlow::Continue:
            return Run(args);

        case ControlFlow::Return:
        default: break;
    }

    return {res, control_flow};
}