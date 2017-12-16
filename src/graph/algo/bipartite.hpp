#pragma once

#include <algorithm>
#include <set>

#include "graph/algo/bfs.hpp"
#include "graph/graph/undirected.hpp"

#include <iostream>

namespace graphbase {
namespace graph {
namespace undirected {
namespace algo {

// IsBipartite returns true if the graph is bipartite
template <class G, class = is_undirected_graph<G>>
bool IsBipartite(const G& g) {
  // This implementation is based on the fact that a graph is bipartite iff it
  // is two-coloured (chromatic number is equal to two).
  enum class Color { Undefined, Blue, Red };

  std::vector<Color> colors(g.vertices().size(), Color::Undefined);
  bool bipartite = true;

  // TODO(https://github.com/kele/graphbase/issues/5): this functor needs to be
  // adjusted as soon as the BFS() spec is complete.
  auto f = [&colors, &bipartite](unsigned first, unsigned last, bool seen) {
    if (colors[last] == Color::Undefined) {
      colors[last] = colors[first] == Color::Blue ? Color::Red : Color::Blue;
    } else if (colors[first] == colors[last]) {
      bipartite = false;
    }
  };

  // The graph might be disconnected, so we need to run the check for each
  // connected component. We do that by running BFS() and colouring vertexes
  // that we've already touched to Blue or Red. If a vertex has not been touched
  // yet, it means it belongs to a different connected component than the ones
  // we've already traversed using BFS().
  for (auto start : g.vertices()) {
    if (not bipartite) return false;

    if (colors[start] == Color::Undefined) {
      colors[start] = Color::Blue;
      BFS(g, start, f);
    }
  }
  return bipartite;
}

}  // namespace algo
}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
