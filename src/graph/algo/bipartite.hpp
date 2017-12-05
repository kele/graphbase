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

template <class G, class = is_undirected_graph<G>>
bool is_bipartite(const G& g) {
  enum class Color { Undefined, Blue, Red };

  std::vector<Color> colors(g.vertices().size(), Color::Undefined);
  bool bipartite = true;

  auto f = [&colors, &bipartite](unsigned first, unsigned last, bool seen) {
    if (colors[last] == Color::Undefined) {
      colors[last] = colors[first] == Color::Blue ? Color::Red : Color::Blue;
    } else if (colors[first] == colors[last]) {
      bipartite = false;
    }
  };

  for (auto start : g.vertices()) {
    if (not bipartite) return false;

    if (colors[start] == Color::Undefined) {
      colors[start] = Color::Blue;
      bfs(g, start, f);
    }
  }
  return bipartite;
}

}  // namespace algo
}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
