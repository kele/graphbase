#pragma once

#include <optional>

#include "query/value.hpp"

namespace query {
namespace conversions {

template <class T> std::optional<T> to(const Value &v) {
  if (v.holds<T>()) {
    return v.get<T>();
  }
  return std::nullopt;
}

} // namespace conversions
} // namespace query
