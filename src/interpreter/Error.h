//
// Created by Jamie on 24/01/2024.
//

#ifndef ERROR_H
#define ERROR_H

#include <iostream>

#include "../Variable.h"

namespace error {
    inline const char *red = "\033[31m";
    inline const char *white = "\033[37m";

    enum class Error {
        Argument,
        Undefined,
        Syntax
    };

    inline void Throw(const Error error, const std::string &message) {
        std::cerr << red;

        switch (error) {
            case Error::Argument: {
                std::cerr << "Argument";
            } break;

            case Error::Undefined: {
                std::cerr << "Undefined";
            } break;

            case Error::Syntax: {
                std::cerr << "Syntax";
            } break;
        }

        std::cerr << " error: " <<  message << white <<  "\n";
        exit(1);
    }
}

#endif //ERROR_H
