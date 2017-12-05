#pragma once

#include "graphsource/graphsource.hpp"

namespace graphbase {
namespace graph {
namespace algo {

class Predicate {
 public:
  virtual bool Test(const graphbase::graphsource::VariantGraph& vg) const = 0;
};

}  // namespace algo
}  // namespace graph
}  // namespace graphbase
