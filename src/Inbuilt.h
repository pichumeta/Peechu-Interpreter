//
// Created by Jamie on 23/01/2024.
//

#ifndef INBUILT_H
#define INBUILT_H

#include <chrono>
#include <cmath>
#include <functional>

#include "Error.h"

namespace inbuilt {
    inline const Any one(1);

    inline Any Decrement(const Any &any) {
        return any - one;
    }

    inline Any Increment(const Any &any) {
        return any + one;
    }

    inline Any Not(const Any &any) {
        return Any(!any.ToBool());
    }

    inline Any Division(const Any &left, const Any &right) {
        return left / right;
    }

    inline Any Multiplication(const Any &left, const Any &right) {
        return left * right;
    }

    inline Any Remainder(const Any &left, const Any &right) {
        return left % right;
    }

    inline Any Addition(const Any &left, const Any &right) {
        return left + right;
    }

    inline Any Subtraction(const Any &left, const Any &right) {
        return left - right;
    }

    inline Any GreaterThan(const Any &left, const Any &right) {
        return left > right;
    }

    inline Any GreaterThanOrEqual(const Any &left, const Any &right) {
        return left >= right;
    }

    inline Any LessThan(const Any &left, const Any &right) {
        return left < right;
    }

    inline Any LessThanOrEqualTo(const Any &left, const Any &right) {
        return left <= right;
    }

    inline Any EqualTo(const Any &left, const Any &right) {
        return left == right;
    }

    inline Any NotEqualTo(const Any &left, const Any &right) {
        return left != right;
    }

    inline Any BitwiseAnd(const Any &left, const Any &right) {
        return null_value;
    }

    inline Any BitwiseOr(const Any &left, const Any &right) {
        return null_value;
    }

    inline Any LogicalAnd(const Any &left, const Any &right) {
        return left && right;
    }

    inline Any LogicalOr(const Any &left, const Any &right) {
        return left || right;
    }

    inline Any DirectAssignment(const Any &left, const Any &right) {
        return const_cast<Any &>(left) = right;
    }

    inline Any SumAssignment(const Any &left, const Any &right) {
        return const_cast<Any &>(left) = left + right;
    }

    inline Any DifferenceAssignment(const Any &left, const Any &right) {
        return const_cast<Any &>(left) = left - right;
    }

    inline Any ProductAssignment(const Any &left, const Any &right) {
        return const_cast<Any &>(left) = left * right;
    }

    inline Any DivisionAssignment(const Any &left, const Any &right) {
        return const_cast<Any &>(left) = left / right;
    }

    inline Any RemainderAssignment(const Any &left, const Any &right) {
        return const_cast<Any &>(left) = left % right;
    }

    inline const std::unordered_map<std::string, std::function<Any(const Any &)>> maths_unary_operators {
        {semantics::tokens::decrement_str, Decrement},
        {semantics::tokens::increment_str, Increment}
    };

    inline const std::unordered_map<std::string, std::function<Any(const Any &)>> logical_unary_operators {
        {semantics::tokens::not_str, Not}
    };

    inline const std::unordered_map<std::string, std::function<Any(const Any &, const Any &)>> maths_operators {
        {semantics::tokens::division_str, Division},
        {semantics::tokens::multiplication_str, Multiplication},
        {semantics::tokens::remainder_str, Remainder},
        {semantics::tokens::addition_str, Addition},
        {semantics::tokens::substraction_str, Subtraction}
    };

    inline const std::unordered_map<std::string, std::function<Any(const Any &, const Any &)>> comparison_operators {
        {semantics::tokens::greater_than_str, GreaterThan},
        {semantics::tokens::greater_than_or_equal_to_str, GreaterThanOrEqual},
        {semantics::tokens::less_than_str, LessThan},
        {semantics::tokens::less_than_or_equal_to_str, LessThanOrEqualTo},
        {semantics::tokens::equal_to_str, EqualTo},
        {semantics::tokens::not_equal_to_str, NotEqualTo}
    };

    inline const std::unordered_map<std::string, std::function<Any(const Any &, const Any &)>> bitwise_operators {
        {semantics::tokens::bitwise_and_str, BitwiseAnd},
        {semantics::tokens::bitwise_or_str, BitwiseOr}
    };

    inline const std::unordered_map<std::string, std::function<Any(const Any &, const Any &)>> logical_operators {
        {semantics::tokens::logical_and_str, LogicalAnd},
        {semantics::tokens::logical_or_str, LogicalOr}
    };

    inline const std::unordered_map<std::string, std::function<Any(const Any &, const Any &)>> assignment_operators {
        {semantics::tokens::direct_assignment_str, DirectAssignment},
        {semantics::tokens::sum_assignment_str, SumAssignment},
        {semantics::tokens::differnce_assignment_str, DifferenceAssignment},
        {semantics::tokens::product_assignment_str, ProductAssignment},
        {semantics::tokens::division_assignment_str, DifferenceAssignment},
        {semantics::tokens::remainder_assignment_str, RemainderAssignment}
    };

    inline Any Print(const std::vector<Any &> &args) {
        std::vector<std::string> strings;
        for (const auto &arg : args)
            strings.emplace_back(arg.ToString());

        std::cout << utils::string::Join(" ", strings);
        return null_value;
    }

    inline Any PrintLine(const std::vector<Any &> &args) {
        Print(args);

        std::cout << "\n";
        return null_value;
    }

    inline Any Log(const std::vector<Any &> &args) {
        if (args.size() == 1) {
            const double result = std::log(args[0].ToNumber());
            return result == static_cast<int>(result) ? Any(static_cast<int>(result)) : Any(result);
        }

        const double result = std::log(args[1].ToNumber()) / std::log(args[0].ToNumber());
        return result == static_cast<int>(result) ? Any(static_cast<int>(result)) : Any(result);
    }

    inline Any Input(const std::vector<Any &> &args) {
        PrintLine(args);
        std::string input;
        std::getline(std::cin, input);
        return Any(std::any(input));
    }

    inline const std::unordered_map<std::string, std::function<Any(const std::vector<Any &> &)>> functions {
        {"print", Print},
        {"println", PrintLine}
    };
}

#endif //INBUILT_H
