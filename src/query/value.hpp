#pragma once

#include "patterns/istream.hpp"

#include <optional>
#include <stdexcept>
#include <type_traits>
#include <variant>
#include <vector>

namespace query {

class Value {
public:
  using Boolean = bool;
  using Integer = int;
  class Stream : public patterns::IStream<std::unique_ptr<Value>> {
  public:
    std::optional<std::unique_ptr<Value>> next() final {
      throw std::logic_error("Value::Stream::next() not implemented.");
    }
  };
  using Vector = std::vector<Value>;

  using variant = std::variant<Boolean, Integer, Stream, Vector>;

  template <class T> static Value from(T v) { return Value(variant(v)); }

  template <class T> std::optional<T> get() const {
    return holds<T>() ? std::make_optional(std::get<T>(m_value)) : std::nullopt;
  }

  template <class T> bool holds() const {
    return std::holds_alternative<T>(m_value);
  }

  Value(const Value &v) = default;
  Value(Value &&v) = default;

private:
  Value() = delete;
  Value(variant v) : m_value(std::move(v)) {}

  variant m_value;
};

} // namespace query
