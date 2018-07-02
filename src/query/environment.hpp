#pragma once

#include "query/binding.hpp"

namespace query {

class Environment {
public:
  static Environment extend(const Environment &env, const Binding &b);
};

} // namespace query
