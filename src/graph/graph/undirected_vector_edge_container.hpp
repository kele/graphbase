#pragma once

#include <functional>
#include <vector>

#include "graph/common/common.hpp"

namespace graphbase {
namespace graph {
namespace undirected {

// AdjacentEdges is a vector for edges adjacent to a vertex.
struct AdjacentEdges : public std::vector<edge_t> {
  explicit AdjacentEdges(unsigned v);

  // Returns the vertex the edges are adjacent to.
  unsigned vertex() const;

 private:
  unsigned m_vertex;
};

// VectorEdgeContainer is an edge container that uses vectors internally. This
// is important because this implies a few properties:
//
// - getting a list (vector) of all edges adjacent to a given vertex costs O(1)
// - traversing all the edges costs O(V + E)
// - adding an edge costs O(1)
// - removing a single edge costs O(E)
// - removing all the edges adjacent to a given vertex costs O(V + E)
//
// Therefore, if your main use case is adding/removing the edges and checking
// if a given edge is present, while rarely needing to traverse all the
// (adjacent) edges, this implementation is not for you.
template <class EdgeData>
class VectorEdgeContainer;

template <>
class VectorEdgeContainer<void> {
 public:
  // Cost: O(V)
  explicit VectorEdgeContainer(size_t n);

  // Returns the number of edges.
  // Cost: O(1)
  size_t size() const;

  // Returns the edges adjacent to a given vertex.
  // Cost: O(1)
  const AdjacentEdges& adjacent(unsigned v) const;

  // Returns a vector containing adjacent edges lists for each vertex. The
  // vector is indexed by vertices.
  // Cost: O(1)
  const std::vector<AdjacentEdges>& vectors() const;

  // Applies a function to each edge.
  // Cost: O(V + E)
  void for_each(std::function<void(const edge_t&)> f) const;

  // Removes edges adjacent to a given vertex.
  // Cost: O(V + E)
  void remove_adjacent(unsigned v);

  // Removes an edge. If there are multiple edges like this, it removes only
  // one of them.
  // Cost: O(V + E)
  void remove(edge_t e);

  // Adds an edge to the graph. Multiple edges are allowed, but no loops.
  // Cost: O(1)
  void add(edge_t e);

 private:
  std::vector<AdjacentEdges> m_edges;
  size_t m_num_edges;
};

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
