#pragma once

#include <memory>

#include "query/value.hpp"

namespace query {

class Environment;

class IExpression {
public:
  virtual Value eval(std::shared_ptr<const Environment> env) const = 0;
  // TODO: implement in subclasses
  // virtual std::type_info typecheck(const Environment &env) const = 0;

  virtual ~IExpression() {}
};

} // namespace query
