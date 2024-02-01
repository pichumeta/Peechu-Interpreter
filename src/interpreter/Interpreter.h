//
// Created by Jamie on 01/02/2024.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Loop.h"

namespace interpreter {

    constexpr float version = 0.12;
    const std::string version_str = std::format("version: {}", version);

    inline void Run(const std::string &file_path) {
        std::string contents = utils::file::GetContents(file_path);

        const auto lexer = std::make_unique<Lexer>(std::move(contents));
        const auto parser = std::make_unique<Parser>(lexer->tokens());

        std::vector<std::shared_ptr<Scope>> functions;
        std::vector<std::shared_ptr<Variable>> variables;
        const auto global_scope = std::make_unique<Scope>(parser->parsed_tokens(), functions, variables);
        global_scope->Run({});
    }

}

#endif //INTERPRETER_H
