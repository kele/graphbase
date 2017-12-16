#pragma once

#include <algorithm>

#include "graph/graph/undirected.hpp"

namespace graphbase {
namespace graph {
namespace undirected {

template <class G, class = is_undirected_graph<G>>
bool IsComplete(const G& g) {
  const size_t size = g.vertices().size();
  for (auto v : g.vertices()) {
    std::vector<bool> present(size, false);
    present[v] = true;

    for (const auto& e : g.edges().adjacent(v)) {
      // Setting both ends of the edge, because we don't know which one is 'v'
      // and we don't care if something is set twice.
      present[e.first()] = true;
      present[e.last()] = true;
    }

    if (not std::all_of(begin(present), end(present),
                        [](bool p) { return p; })) {
      return false;
    }
  }
  return true;
}

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
