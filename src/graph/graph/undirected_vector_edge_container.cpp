#include "graph/graph/undirected_vector_edge_container.hpp"

#include "estd/estd.hpp"

namespace graphbase {
namespace graph {
namespace undirected {

////////////////////////////////////////////////////////////////////////////////
// AdjacentEdges implementation
AdjacentEdges::AdjacentEdges(unsigned v) : m_vertex(v) {}

unsigned AdjacentEdges::vertex() const { return m_vertex; }

////////////////////////////////////////////////////////////////////////////////
// VectorEdgeContainer implementation for edges with no data.
VectorEdgeContainer<void>::VectorEdgeContainer(size_t n) : m_num_edges(0) {
  m_edges.reserve(n);
  for (unsigned v = 0; v < n; v++) {
    m_edges.emplace_back(v);
  }
}

size_t VectorEdgeContainer<void>::size() const { return m_num_edges; }

const AdjacentEdges& VectorEdgeContainer<void>::adjacent(unsigned v) const {
  estd::require(v < m_edges.size(), "vertex index too high",
                "VectorEdgeContainer::adjacent()");
  return m_edges[v];
}

const std::vector<AdjacentEdges>& VectorEdgeContainer<void>::vectors() const {
  return m_edges;
}

void VectorEdgeContainer<void>::for_each(
    std::function<void(const edge_t&)> f) const {
  for (const auto& edges : m_edges) {
    for (const auto& e : edges) {
      if (edges.vertex() == e.first()) {
        // Each edge is present in two AdjacentEdges containers. But since the
        // edges are normalized, each edge will pass the predicate below only
        // once.
        f(e);
      }
    }
  }
}

void VectorEdgeContainer<void>::remove_adjacent(unsigned v) {
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

void VectorEdgeContainer<void>::remove(edge_t e) {
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

void VectorEdgeContainer<void>::add(edge_t e) {
  estd::require(e.first() != e.last(), "illegal loop",
                "VectorEdgeContainer::add()");

  m_num_edges++;
  m_edges[e.first()].push_back(e);
  m_edges[e.last()].push_back(e);
}

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
