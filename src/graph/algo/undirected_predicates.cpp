#include "graph/algo/undirected_predicates.hpp"

#include "graph/algo/bipartite.hpp"

namespace graphbase {
namespace graph {
namespace undirected {
namespace predicates {

bool IsBipartite::Test(const graphbase::graphsource::VariantGraph &vg) const {
  if (not vg.IsUndirected()) {
    return false;
  }
  return graph::undirected::algo::IsBipartite(*vg.Undirected());
}

} // namespace predicates
} // namespace undirected
} // namespace graph
} // namespace graphbase
