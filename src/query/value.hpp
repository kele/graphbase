#pragma once

#include <experimental/any>
#include <optional>
#include <stdexcept>
#include <type_traits>

namespace query {

class Value {
public:
  template <class T> static Value from(T v) {
    return Value(std::experimental::any(v));
  }

  template <class T> std::optional<T> get() const {
    if (m_value.empty()) {
      return std::nullopt;
    }
    if (typeid(T) != m_value.type()) {
      return std::nullopt;
    }
    return std::experimental::any_cast<T>(m_value);
  }

  Value(const Value &v) : m_value(v.m_value) {}
  Value(Value &&v) : m_value(std::move(v.m_value)) {}

private:
  Value() = delete;
  explicit Value(std::experimental::any v) : m_value(v) {}

  std::experimental::any m_value;
};

} // namespace query
