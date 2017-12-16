#pragma once

#include "graph/algo/predicates.hpp"

namespace graphbase {
namespace graph {
namespace undirected {
namespace predicates {

class IsBipartite : public graphbase::graph::predicates::Predicate {
 public:
  bool Test(const graphbase::graphsource::VariantGraph& vg) const override;
};

}  // namespace predicates
}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
