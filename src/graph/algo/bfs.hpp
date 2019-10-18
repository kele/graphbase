#pragma once

#include <algorithm>
#include <queue>
#include <type_traits>

#include "graph/graph/undirected.hpp"

namespace graphbase {
namespace undirected {
namespace algo {

// BFS performs a breadth first search on a given graph provided a starting
// point.
// TODO(https://github.com/kele/graphbase/issues/2): add constraints for F.
// TODO(https://github.com/kele/graphbase/issues/5): write better spec (e.g. on
// which edges is the F functor called)
template <class G, class = is_undirected_graph<G>, class F>
void BFS(const G &g, unsigned start, F f) {
  std::vector<bool> visited(g.vertices().size(), false);
  std::vector<bool> seen(g.vertices().size(), false);
  seen[start] = true;

  std::queue<unsigned> q;
  q.push(start);

  while (not q.empty()) {
    unsigned v = q.front();
    q.pop();

    if (visited[v])
      continue;
    visited[v] = true;

    for (const auto &e : g.edges().adjacent(v)) {
      unsigned u = v == e.first() ? e.last() : e.first();
      f(v, u, !seen[u]);
      if (seen[u])
        continue;
      q.push(u);
      seen[u] = true;
    }
  }
}

template <class G, class = is_undirected_graph<G>, class F,
          class = std::is_invocable<F, G, unsigned, bool>>
void BFS(const G &g, unsigned start, const F &&f) {
  BFS(g, start, std::ref(f));
}

} // namespace algo
} // namespace undirected
} // namespace graphbase
