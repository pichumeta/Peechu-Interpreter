//
// Created by Jamie on 17/01/2024.
//

#ifndef ANY_H
#define ANY_H

#include <any>

#include "utils/Utils.h"

class Any {
public:
    static bool IsLiteral(const std::string &literal) noexcept;

    Any() noexcept = default;

    explicit Any(std::any any) noexcept;
    explicit Any(const std::string &literal);

    virtual ~Any() = default;

    [[nodiscard]] virtual bool pass_by_ref() const noexcept { return false; };
    virtual void set_name(const std::string &name) {};

    Any &operator=(const std::any &any) noexcept;

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

    [[nodiscard]] std::any any() const noexcept;
    void set_any(const std::any &any) noexcept;

    [[nodiscard]] bool ToBool() const noexcept;
    [[nodiscard]] double ToNumber() const noexcept;
    [[nodiscard]] std::string ToString() const noexcept;
    [[nodiscard]] std::vector<Any> ToVector() const noexcept;

private:
    inline static const std::string vector_delim = ", ";

    template<class T>
    [[nodiscard]] T AnyCast() const noexcept;

    std::any m_any;
};

inline const Any null_value(static_cast<std::any>(nullptr));

#endif //ANY_H
