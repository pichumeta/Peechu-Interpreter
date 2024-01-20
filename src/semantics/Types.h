//
// Created by Jamie on 20/01/2024.
//

#ifndef TYPES_H
#define TYPES_H

#include "../Any.h"

namespace semantics::types {
    inline const size_t bool_code = typeid(bool).hash_code();
    inline const size_t int_code = typeid(int).hash_code();
    inline const size_t float_code = typeid(double).hash_code();
    inline const size_t string_code = typeid(std::string).hash_code();
    inline const size_t vector_code = typeid(std::vector<Any>).hash_code();
}

#endif //TYPES_H
