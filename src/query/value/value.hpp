#pragma once

#include "query/value/boolean.hpp"
#include "query/value/graph.hpp"
#include "query/value/integer.hpp"
#include "query/value/stream.hpp"
#include "query/value/vector.hpp"

#include <optional>
#include <stdexcept>
#include <type_traits>
#include <variant>
#include <vector>

namespace query {
namespace value {

class Value {
public:
  using variant = std::variant<Boolean, Integer, Stream, Vector, Graph>;

  template <class T> static Value of(T v) { return Value(variant(v)); }

  template <class T> const T &get() const { return std::get<T>(m_value); }

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

} // namespace value
} // namespace query
