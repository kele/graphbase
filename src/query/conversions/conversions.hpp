#pragma once

#include <optional>

#include "query/value/value.hpp"

namespace query {
namespace conversions {

template <class T> std::optional<T> to(const value::Value &v) {
  if (v.holds<T>()) {
    return v.get<T>();
  }
  return std::nullopt;
}

} // namespace conversions
} // namespace query
