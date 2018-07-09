#pragma once

#include "query/conversions/conversions.hpp"
#include "query/environment.hpp"
#include "query/expression.hpp"

#include <map>
#include <stdexcept>
#include <typeinfo>

namespace query {

template <class T>
std::optional<T> evaluate(const Environment &env, const IExpression &expr) {
  return conversions::to<T>(expr.eval(env));
}

} // namespace query
