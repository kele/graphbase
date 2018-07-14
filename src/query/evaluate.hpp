#pragma once

#include "query/conversions/conversions.hpp"
#include "query/environment.hpp"
#include "query/iexpression.hpp"

#include <map>
#include <stdexcept>
#include <typeinfo>

namespace query {

template <class T>
std::optional<T> evaluate(std::shared_ptr<const Environment> env,
                          const IExpression &expr) {
  return conversions::to<T>(expr.eval(env));
}

} // namespace query
