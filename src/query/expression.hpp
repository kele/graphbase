#pragma once

#include "estd/generator.hpp"
#include "query/value.hpp"

namespace query {

class Expression {
public:
  bool is_generator() const;
  operator estd::generator<Value>() const;
};

} // namespace query
