//
// Created by Jamie on 19/01/2024.
//

#ifndef TOKENS_H
#define TOKENS_H

#include <unordered_map>

namespace tokens {
    enum class Tokens {
        // Keywords:
        Else,
        Function,
        If,
        Loop,
        PassByReference,
        VariableInitialiser,

        // Maths unary operators:
        Decrement,
        Increment,

        // Logical unary operators:
        Not,

        // Maths operators (left to right):
        PointerToMember,
        Division,
        Multiplication,
        Remainder,

        // Comparison operators (left to right):
        // (relational)
        GreaterThan,
        GreaterThanOrEqualTo,
        LessThan, // I usually prefer to say lower than or smaller than
        LessThanOrEqualTo,
        // (equality)
        EqualTo,
        NotEqualTo,

        // Bitwise operators (left to right):
        BitwiseAnd,
        BitwiseOr,

        // Logical operators (left to right):
        LogicalAnd,
        LogicalOr,

        // Separators:
        Comma,
        OpenBracket,
        ClosedBracket,

        // Whitespace:
        Flush,
        NewLine,
        Space,
    };


}

#endif //TOKENS_H
