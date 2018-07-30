#pragma once

#include "patterns/istream.hpp"

#include <optional>
#include <stdexcept>
#include <type_traits>
#include <variant>
#include <vector>

namespace query {

class Value;
using Boolean = bool;

struct Integer {
  Integer(int v) : value(v) {}
  int value;
  operator int() const { return value; }
};

class Stream : public patterns::IStream<std::unique_ptr<Value>> {
public:
  std::optional<std::unique_ptr<Value>> next() final {
    throw std::logic_error("Value::Stream::next() not implemented.");
  }
};

// TODO: get rid of vector
using Vector = std::vector<Value>;

class Value {
public:
  using variant = std::variant<Boolean, Integer, Stream, Vector>;

  template <class T> static Value of(T v) { return Value(variant(v)); }

  template <class T> const T& get() const {
    return std::get<T>(m_value);
  }

  template <class T> std::optional<T> try_get() const {
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
