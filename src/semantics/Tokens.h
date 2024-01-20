//
// Created by Jamie on 19/01/2024.
//

#ifndef TOKENS_H
#define TOKENS_H

#include <unordered_map>

#include "../utils/Utils.h"

namespace semantics::tokens {
    enum class Tokens {
        // Keywords:
        Else,
        Function,
        If,
        Loop,
        PassByReference,
        VariableInitialiser,

        //
        FunctionCall,
        MemberAccess,

        // Maths unary operators:
        Decrement,
        Increment,

        // Logical unary operators:
        Not,

        // Maths operators (left to right):
        Division,
        Multiplication,
        Remainder,

        Addition,
        Subtraction,

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

    inline const std::unordered_map<std::string, Tokens> keywords {
        {"else", Tokens::Else},
        {"fun", Tokens::Function},
        {"if", Tokens::If},
        {"loop", Tokens::Loop},
        {"ref", Tokens::PassByReference},
        {"let", Tokens::VariableInitialiser}
    };

    inline const std::unordered_map<std::string, Tokens> maths_unary_operators {
        {"--", Tokens::Decrement},
        {"++", Tokens::Increment}
    };

    inline const std::unordered_map<std::string, Tokens> logical_unary_operators {
        {"!", Tokens::Not}
    };

    inline const std::unordered_map<std::string, Tokens> maths_operators {
        {"/", Tokens::Division},
        {"*", Tokens::Multiplication},
        {"%", Tokens::Remainder},

        {"+", Tokens::Addition},
        {"-", Tokens::Subtraction}
    };

    inline const std::unordered_map<std::string, Tokens> comparison_operators {
        {">", Tokens::GreaterThan},
        {">=", Tokens::GreaterThanOrEqualTo},
        {"<", Tokens::LessThan},
        {"<=", Tokens::LessThanOrEqualTo},

        {"==", Tokens::EqualTo},
        {"!=", Tokens::NotEqualTo}
    };

    inline const std::unordered_map<std::string, Tokens> bitwise_operators {
        {"&", Tokens::BitwiseAnd},
        {"|", Tokens::BitwiseOr}
    };

    inline const std::unordered_map<std::string, Tokens> logical_operators {
        {"&&", Tokens::LogicalAnd},
        {"||", Tokens::LogicalOr}
    };

    inline const std::unordered_map<std::string, Tokens> separators {
        {",", Tokens::Comma},
        {"(", Tokens::OpenBracket},
        {")", Tokens::ClosedBracket}
    };

    inline const std::unordered_map<std::string, Tokens> whitespace {
        {"\r", Tokens::Flush},
        {"\n", Tokens::NewLine},
        {" ", Tokens::Space}
    };
}

#endif //TOKENS_H
