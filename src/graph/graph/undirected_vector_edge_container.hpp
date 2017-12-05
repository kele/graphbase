#pragma once

namespace graphbase {
namespace graph {
namespace undirected {

template <class EdgeData = void>
class VectorEdgeContainer {};

/* TODO(kele): there's a bit of optimization opportunity left here. Edge does
 * not have to be a pair, it'd be perfectly fine if it were just the vertex
 * index. */
struct AdjacentEdges : public std::vector<edge_t> {
  explicit AdjacentEdges(unsigned v) : m_vertex(v) {}
  unsigned vertex() const { return m_vertex; }

 private:
  unsigned m_vertex;
};

/* TODO(kele): there's a bit of optimization opportunity left here. Edge does
 * not have to be a pair, it'd be perfectly fine if it were just the vertex
 * index. */
template <>
class VectorEdgeContainer<void> {
 public:
  VectorEdgeContainer(size_t n) : m_num_edges(0) {
    m_edges.reserve(n);
    for (unsigned v = 0; v < n; v++) {
      m_edges.emplace_back(v);
    }
  }

  /* Returns the number of edges. */
  size_t size() const { return m_num_edges; }

  /* Returns the edges adjacent to a given vertex. */
  const AdjacentEdges& adjacent(unsigned v) const {
    estd::require(v < m_edges.size(), "vertex index too high",
                  "VectorEdgeContainer::adjacent()");
    return m_edges[v];
  }

  /* Returns a vector containing adjacent edges lists for each vertex. The
   * vector is indexed by vertices. */
  const std::vector<AdjacentEdges>& vectors() const { return m_edges; }

  /* Applies a function to each edge. */
  void for_each(std::function<void(const edge_t&)> f) const {
    for (const auto& edges : m_edges) {
      for (const auto& e : edges) {
        if (edges.vertex() == e.first()) {
          f(e);
        }
      }
    }
  }

  /* Removes edges adjacent to a given vertex. */
  void remove_adjacent(unsigned v) {
    estd::require(v < m_edges.size(), "vertex index too high",
                  "VectorEdgeContainer::remove_adjacent()");

    m_num_edges -= m_edges[v].size();
    m_edges[v].clear();

    /* Removing the other side of each edge. */
    for (auto& edges : m_edges) {
      auto it = remove_if(begin(edges), end(edges), [v](const edge_t& edge) {
        return edge.last() == v || edge.first() == v;
      });
      /* We are not decrementing the count of edges here as we did that already.
       */
      edges.erase(it, end(edges));
    }
  }

  /* Removes an edge. If there are multiple edges like this, it removes only
   * one of them. */
  void remove(edge_t e) {
    bool edge_found = false;
    for (auto v : {e.first(), e.last()}) {
      auto& adjacent = m_edges[v];
      auto it = std::find(begin(adjacent), end(adjacent), e);
      if (it != end(adjacent)) {
        edge_found = true;
        /* Since the order of the vertices is not relevant, we can optimize
         * here by copying the last edge in place of the one we want to remove
         * and shrinking the list by one. */
        *it = adjacent.back();
        adjacent.pop_back();
      }
    }
    if (edge_found) {
      m_num_edges--;
    }
  }

  /* Adds an edge to the graph. Multiple edges are allowed, but no loops. */
  void add(edge_t e) {
    estd::require(e.first() != e.last(), "illegal loop",
                  "VectorEdgeContainer::add()");

    m_num_edges++;
    m_edges[e.first()].push_back(e);
    m_edges[e.last()].push_back(e);
  }

 private:
  std::vector<AdjacentEdges> m_edges;
  size_t m_num_edges;
};

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
