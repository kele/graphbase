#pragma once

#include <memory>

#include "query/value.hpp"

namespace query {

class Environment;

class IExpression {
public:
  virtual Value eval(std::shared_ptr<const Environment> env) const = 0;

  virtual ~IExpression() {}
};

} // namespace query
