#pragma once

#include "graphsource/graphsource.hpp"

namespace graphbase {
namespace predicates {

template<class G>
class Predicate {
public:
  using GraphType = G;

  virtual bool Test(const GraphType &vg) const = 0;
};

} // namespace predicates
} // namespace graphbase
