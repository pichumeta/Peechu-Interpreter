//
// Created by Jamie on 17/01/2024.
//

#include <ranges>

#include "semantics/Semantics.h"

bool Any::IsLiteral(const std::string &literal) noexcept {
    try {
        Any a(literal);
        return true;
    } catch (...) {
        return false;
    }
}

Any::Any(std::any any) noexcept : m_any(std::move(any)) {

}

Any::Any(const std::string &literal) {
    if (literal == "false" || literal == "true")
        m_any = literal == "true";
    else if (literal.find('"') != std::string::npos) {
        std::string string_rep = literal;
        string_rep.erase(0, 1);
        string_rep.erase(string_rep.length() - 1, 1);

        m_any = string_rep;
    } else if (literal.find('[') != std::string::npos) {
        std::string string_rep = literal;
        string_rep.erase(0, 1);
        string_rep.erase(string_rep.length() - 1, 1);

        std::vector<Any> vector_rep;
        for (const std::vector elements = utils::string::Split(string_rep, vector_delim);
            const auto &element : elements) {
            vector_rep.emplace_back(element);
        }

        m_any = vector_rep;
    } else if (literal.find('.') != std::string::npos)
        m_any = std::stod(literal);
    else
        m_any = std::stoi(literal);
}

Any &Any::operator=(const std::any &any) noexcept {
    m_any = any;
    return *this;
}

std::any Any::any() const noexcept {
    return m_any;
}

void Any::set_any(const std::any &any) noexcept {
    m_any = any;
}

template<class T>
T Any::AnyCast() const noexcept {
    return std::any_cast<T>(*this);
}

Any Any::operator&&(const Any &other) const noexcept {
    return Any(ToBool() && other.ToBool());
}

Any Any::operator||(const Any &other) const noexcept {
    return Any(ToBool() || other.ToBool());
}

Any Any::operator==(const Any &other) const noexcept {
    return Any(ToString() == other.ToString());
}

Any Any::operator!=(const Any &other) const noexcept {
    return Any(ToString() != other.ToString());
}

Any Any::operator>(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || type_code == semantics::types::float_code) {
        result = ToNumber() > other.ToNumber();
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = ToString().length() > other.ToString().length();
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = ToVector().size() > other.ToVector().size();

end:
    return result;
}

Any Any::operator>=(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || type_code == semantics::types::float_code) {
        result = ToNumber() >= other.ToNumber();
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = ToString().length() >= other.ToString().length();
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = ToVector().size() >= other.ToVector().size();

end:
    return result;
}

Any Any::operator<(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || type_code == semantics::types::float_code) {
        result = ToNumber() < other.ToNumber();
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = ToString().length() < other.ToString().length();
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = ToVector().size() < other.ToVector().size();

end:
    return result;
}

Any Any::operator<=(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || type_code == semantics::types::float_code) {
        result = ToNumber() <= other.ToNumber();
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = ToString().length() <= other.ToString().length();
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = ToVector().size() <= other.ToVector().size();

end:
    return result;
}

Any Any::operator+(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || semantics::types::float_code) {
        const double _result = ToNumber() + other.ToNumber();
        result = _result == static_cast<int>(_result) ? static_cast<int>(_result) : _result;
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        const std::string string = ToString();
        const std::string other_string = other.ToString();

        result = std::any(string + other_string);

        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        std::vector<Any> vector = ToVector();
        const std::vector<Any> other_vector = other.ToVector();
        vector.insert(vector.begin(), other_vector.begin(), other_vector.end());

        result = vector;
    }

end:
    return result;
}

Any Any::operator-(const Any &other) const noexcept {
    Any result = null_value;

    if (const size_t type_code = m_any.type().hash_code();
        type_code == semantics::types::int_code || semantics::types::float_code) {
        const double _result = ToNumber() - other.ToNumber();
        result = _result == static_cast<int>(_result) ? static_cast<int>(_result) : _result;
    }

    return result;
}

Any Any::operator*(const Any &other) const noexcept {
    Any result = null_value;

    if (const size_t type_code = m_any.type().hash_code();
        type_code == semantics::types::int_code || semantics::types::float_code) {
        const double _result = ToNumber() * other.ToNumber();
        result = _result == static_cast<int>(_result) ? static_cast<int>(_result) : _result;
    }

    return result;
}

Any Any::operator/(const Any &other) const noexcept {
    Any result = null_value;

    if (const size_t type_code = m_any.type().hash_code();
        type_code == semantics::types::int_code || semantics::types::float_code) {
        const double _result = ToNumber() / other.ToNumber();
        result = _result == static_cast<int>(_result) ? static_cast<int>(_result) : _result;
    }

    return result;
}

Any Any::operator%(const Any &other) const noexcept {
    Any result = null_value;

    if (const size_t type_code = m_any.type().hash_code();
        type_code == semantics::types::int_code || semantics::types::float_code) {
        const double _result = static_cast<int>(ToNumber()) % static_cast<int>(other.ToNumber());
        result = _result == static_cast<int>(_result) ? static_cast<int>(_result) : _result;
    }

    return result;
}

bool Any::ToBool() const noexcept {
    bool result = true;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        result = AnyCast<bool>();
        goto end;
    }

    if (type_code == semantics::types::int_code || semantics::types::float_code)
        result = ToNumber() != 0;

end:
    return result;
}

double Any::ToNumber() const noexcept {
    double result = 0;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code) {
        result = AnyCast<int>();
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        result = AnyCast<double>();
        goto end;
    }

    if (type_code == semantics::types::string_code)
        result = std::stod(AnyCast<std::string>());

end:
    return result;
}

std::string Any::ToString() const noexcept {
    std::string result;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code) {
        result = std::to_string(AnyCast<int>());
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        result = std::to_string(AnyCast<double>());
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = AnyCast<std::string>();
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        std::vector<std::string> vector;
        std::ranges::copy(std::views::transform(AnyCast<std::vector<Any>>(), [](const Any &any) {
            return any.ToString();
        }), std::back_inserter(vector));
    }

end:
    return result;
}

std::vector<Any> Any::ToVector() const noexcept {
    std::vector<Any> result;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code) {
        result.emplace_back(AnyCast<int>());
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        result.emplace_back(AnyCast<double>());
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result.emplace_back(AnyCast<std::string>());
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = AnyCast<std::vector<Any>>();

end:
    return result;
}