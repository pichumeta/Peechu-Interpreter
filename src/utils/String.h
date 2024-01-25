//
// Created by Jamie on 17/01/2024.
//

#ifndef STRING_H
#define STRING_H

#include <concepts>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace utils::string {
    template<class T>
    concept Container = requires(T a)
    {
        { a.begin() } -> std::same_as<typename T::const_iterator>;
        { a.end() } -> std::same_as<typename T::const_iterator>;
    };

    template<class T>
    std::string Join(const char *delim, const std::vector<T> &elements) noexcept {
        const T *last = &elements[elements.size() - 1];

        std::stringstream string_stream;
        for (const auto &element : elements) {
            string_stream << element;
            if (&element == last) break;
            string_stream << delim;
        };

        return string_stream.str();
    }

    inline std::vector<std::string> Split(const std::string &str, const std::string &delim) noexcept {
        const size_t delim_len = delim.length();

        std::vector<std::string> result;

        std::string substr;
        for (const auto &c : str) {
            substr += c;

            const size_t length_difference = substr.length() - delim_len;
            if (length_difference == -1) continue;

            if (substr.substr(length_difference, delim_len) == delim) {
                substr.erase(length_difference, delim_len);
                result.emplace_back(substr);
                substr.clear();
            }
        };

        result.emplace_back(substr);

        return result;
    }
}

#endif //STRING_H
