#pragma once

#include <vector>

#include "estd/estd.hpp"
#include "graph/common/common.hpp"
#include "graph/graph/undirected_vector_edge_container.hpp"

namespace graphbase {
namespace graph {
namespace undirected {

// EmptyGraphBase should be used for every undirected graph implementation. It
// it used in the is_undirected_graph predicate to check whether a graph is
// undirected or not.
class EmptyGraphBase {
 public:
  constexpr GraphType Type() const { return GraphType::Undirected; }
};

// is_undirected_graph checks whether the type is marked as one implementing an
// undirected graph.
template <class G>
using is_undirected_graph =
    std::enable_if_t<std::is_base_of_v<EmptyGraphBase, G>>;

// Undirected graph.
template <class VertexData = void,
          class EdgeContainer = VectorEdgeContainer<void>>
class Graph;

// Undirected graph with no data associated to edges.
template <class EdgeContainer>
class Graph<void, EdgeContainer> : EmptyGraphBase {
 public:
  // Creates a graph with `n` vertices.
  // Cost: O(V)
  explicit Graph(size_t n);

  // Vertices.
  // Cost: O(1)
  const std::vector<unsigned>& vertices() const;

  // Edges in the graph.
  // Cost: O(1)
  const EdgeContainer& edges() const;

  // Edges in the graph.
  // Cost: O(1)
  EdgeContainer& edges();

 private:
  EdgeContainer m_edges;
  std::vector<unsigned> m_vertices;
};

// BasicGraph is an undirected graph with no data tied to vertices nor edges.
using BasicGraph = Graph<void, VectorEdgeContainer<void>>;

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase

#include "graph/graph/undirected_impl.hpp"
