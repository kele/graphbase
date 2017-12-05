#pragma once

#include "graph/algo/predicates.hpp"

namespace graphbase {
namespace graph {
namespace undirected {
namespace algo {

class IsBipartite : public graph::algo::Predicate {
 public:
  bool Test(const graphbase::graphsource::VariantGraph& vg) const override;
};

}  // namespace algo
}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
