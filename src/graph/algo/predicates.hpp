#pragma once

#include "graphsource/graphsource.hpp"

namespace graphbase {
namespace graph {
namespace predicates {

class Predicate {
public:
  virtual bool Test(const graphbase::graphsource::VariantGraph &vg) const = 0;
};

} // namespace predicates
} // namespace graph
} // namespace graphbase
