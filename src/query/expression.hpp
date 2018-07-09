#pragma once

#include "estd/generator.hpp"
#include "query/value.hpp"

namespace query {

class Environment;

class IExpression {
public:
  virtual Value eval(const Environment &env) const = 0;

  virtual ~IExpression() {}
};

template <class Derived> class Expression : public IExpression {
public:
  Value eval(const Environment &env) const final {
    return static_cast<const Derived *>(this)->evalImpl(env);
  }
};

} // namespace query
