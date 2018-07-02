#pragma once

#include "query/environment.hpp"
#include "query/expression.hpp"

#include <stdexcept>

namespace query {

template <class T> T evaluate(const Environment &env, const Expression &expr) {
  throw std::runtime_error("Not implemented.");
}

} // namespace query
