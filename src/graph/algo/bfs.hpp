
#pragma once

#include <algorithm>
#include <queue>
#include <type_traits>

#include "graph/graph/undirected.hpp"

namespace graphbase {
namespace graph {
namespace undirected {

template <class G, class = is_undirected_graph<G>, class F,
          class = std::is_invocable<F, G, unsigned, unsigned>>
void bfs(const G& g, unsigned start, F f) {
  std::vector<bool> visited(g.vertices().size(), false);
  std::vector<bool> seen(g.vertices().size(), false);
  seen[start] = true;

  std::queue<unsigned> q;
  q.push(start);

  while (not q.empty()) {
    unsigned v = q.front();
    q.pop();

    if (visited[v]) continue;
    visited[v] = true;

    for (const auto& e : g.edges().adjacent(v)) {
      unsigned u = v == e.first() ? e.last() : e.first();
      f(v, u, seen[u]);
      if (seen[u]) continue;
      q.push(u);
      seen[u] = true;
    }
  }
}

template <class G, class = is_undirected_graph<G>, class F,
          class = std::is_invocable<F, G, unsigned, unsigned>>
void bfs(const G& g, unsigned start, const F&& f) {
  bfs(g, start, std::ref(f));
}

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
