#pragma once

#include "estd/estd.hpp"
#include "graph/common/common.hpp"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "graph/graph/undirected_vector_edge_container.hpp"

namespace graphbase {
namespace graph {
namespace undirected {

class EmptyGraphBase {
 public:
  constexpr GraphType Type() const { return GraphType::Undirected; }
};

template <class G>
using is_undirected_graph =
    std::enable_if_t<std::is_base_of_v<EmptyGraphBase, G>>;

/* Undirected graph.
 *
 * The graph is parametrized by the edge type, thus allowing the graph to have
 * any data associated to the edges.
 *
 * This implementation allows for loops and multiple edges between the same
 * vertices.
 */
template <class VertexData = void,
          class EdgeContainer = VectorEdgeContainer<void>>
class Graph;

template <class EdgeContainer>
class Graph<void, EdgeContainer> : EmptyGraphBase {
 public:
  explicit Graph(size_t n);

  const std::vector<unsigned>& vertices() const;

  /* Remove adjacent edges */
  void remove_adjacent_edges(unsigned v);

  /* Edges in the graph */
  const EdgeContainer& edges() const;

  /* Performs an operation on each edge */
  void for_each_edge(std::function<void(const edge_t&)>) const;

  /* Adds an edge to the graph. */
  void add_edge(edge_t edge);

  /* Removes an edge from the graph. */
  void remove_edge(edge_t edge);

 private:
  EdgeContainer m_edges;
  std::vector<unsigned> m_vertices;
};

using BasicGraph = Graph<>;

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase

#include "graph/graph/undirected_impl.hpp"
