//
// Created by Jamie on 17/01/2024.
//

#ifndef ANY_H
#define ANY_H

#include <any>
#include <utility>

#include "semantics/Semantics.h"

class Any {
public:
    static bool IsLiteral(const std::string &literal) noexcept;

    explicit Any(std::any any) noexcept;
    explicit Any(const std::string &literal);

    Any operator&&(const Any &other) const noexcept;
    Any operator||(const Any &other) const noexcept;
    Any operator==(const Any &other) const noexcept;
    Any operator!=(const Any &other) const noexcept;
    Any operator>(const Any &other) const noexcept;
    Any operator>=(const Any &other) const noexcept;
    Any operator<(const Any &other) const noexcept;
    Any operator<=(const Any &other) const noexcept;

    Any operator+(const Any &other) const noexcept;
    Any operator-(const Any &other) const noexcept;
    Any operator*(const Any &other) const noexcept;
    Any operator/(const Any &other) const noexcept;
    Any operator%(const Any &other) const noexcept;

    Any &operator[](const Any &other) const noexcept;

    [[nodiscard]] std::any any() const noexcept;
    void set_any(const std::any &any) noexcept;

    [[nodiscard]] bool ToBool() const noexcept;
    [[nodiscard]] double ToNumber() const noexcept;
    [[nodiscard]] std::string ToString() const noexcept;

private:
    inline static Any null_value = nullptr;

    template<class T>
    [[nodiscard]] T &AnyCast() const noexcept;

    std::any m_any;
};

inline const size_t bool_code = typeid(bool).hash_code();
inline const size_t int_code = typeid(int).hash_code();
inline const size_t float_code = typeid(double).hash_code();
inline const size_t string_code = typeid(std::string).hash_code();
inline const size_t vector_code = typeid(std::vector<Any>).hash_code();

#endif //ANY_H
