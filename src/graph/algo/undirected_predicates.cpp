#include "graph/algo/undirected_predicates.hpp"

#include "graph/algo/bipartite.hpp"

namespace graphbase {
namespace undirected {
namespace predicates {

bool IsBipartite::Test(const BasicGraph &g) const {
  return undirected::algo::IsBipartite(g);
}

} // namespace predicates
} // namespace undirected
} // namespace graphbase
