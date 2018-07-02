#pragma once

#include <stdexcept>

namespace query {
class Value {
public:
  template <class T> static Value from(T &&v) {
    throw std::runtime_error("Not implemented.");
  }
};

} // namespace query
