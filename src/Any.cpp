//
// Created by Jamie on 17/01/2024.
//

#include "semantics/Types.h"

bool Any::IsLiteral(const std::string &literal) noexcept {
    try {
        Any a(literal);
        return true;
    } catch (...) {
        return false;
    }
}

Any::Any(std::any any) : m_any(std::move(any)) {

}

Any::Any(const std::string &literal) {
    if (literal == "false" || literal == "true")
        m_any = literal == "true";
    else if (literal.find('"') != std::string::npos) {
        std::string string_rep = literal;
        string_rep.erase(0, 1);
        string_rep.erase(string_rep.length() - 1, 1);

        m_any = string_rep;
    } else if (literal.find('.') != std::string::npos)
        m_any = std::stod(literal);
    else
        m_any = std::stoi(literal);
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
        result = Any(ToNumber() > other.ToNumber());
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = Any(ToString().length() > other.ToString().length());
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = Any(ToVector().size() > other.ToVector().size());

end:
    return result;
}

Any Any::operator>=(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || type_code == semantics::types::float_code) {
        result = Any(ToNumber() >= other.ToNumber());
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = Any(ToString().length() >= other.ToString().length());
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = Any(ToVector().size() >= other.ToVector().size());

end:
    return result;
}

Any Any::operator<(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::int_code || type_code == semantics::types::float_code) {
        result = Any(ToNumber() < other.ToNumber());
        goto end;
    }

    if (type_code == semantics::types::string_code) {
        result = Any(ToString().length() < other.ToString().length());
        goto end;
    }

    if (type_code == semantics::types::vector_code)
        result = Any(ToVector().size() < other.ToVector().size());

end:
    return result;
}

Any Any::operator<=(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        goto end;
    }

    if (type_code == semantics::types::int_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        goto end;
    }

    end:
        return result;
}

Any Any::operator+(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        goto end;
    }

    if (type_code == semantics::types::int_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        goto end;
    }

    end:
        return result;
}

Any Any::operator-(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        goto end;
    }

    if (type_code == semantics::types::int_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        goto end;
    }

    end:
        return result;
}

Any Any::operator*(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        goto end;
    }

    if (type_code == semantics::types::int_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        goto end;
    }

    end:
        return result;
}

Any Any::operator/(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        goto end;
    }

    if (type_code == semantics::types::int_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        goto end;
    }

    end:
        return result;
}

Any Any::operator%(const Any &other) const noexcept {
    Any result = null_value;
    const size_t type_code = m_any.type().hash_code();

    if (type_code == semantics::types::bool_code) {
        goto end;
    }

    if (type_code == semantics::types::int_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::float_code) {
        goto end;
    }

    if (type_code == semantics::types::vector_code) {
        goto end;
    }

end:
    return result;
}

double Any::ToNumber() const noexcept {
    double result = 0;

    if (const size_t type_code = m_any.type().hash_code();
        type_code == semantics::types::int_code ||
        type_code == semantics::types::float_code)
        result = type_code == semantics::types::int_code ? AnyCast<int>() : AnyCast<double>();

end:
    return result;
}