#include "graphsource/graphsource.hpp"

#include <memory>
#include <typeindex>
#include <variant>

#include "estd/estd.hpp"
#include "graph/graph/directed.hpp"
#include "graph/graph/undirected.hpp"
#include "graphsource/kinds.hpp"

namespace graphbase {
namespace graphsource {

using graph::directed::BasicDigraph;
using undirected::BasicGraph;

////////////////////////////////////////////////////////////////////////////////
// VariantGraph implementation
VariantGraph::VariantGraph(std::shared_ptr<const BasicGraph> g) : m_graph(g) {}

VariantGraph::VariantGraph(std::shared_ptr<const BasicDigraph> g)
    : m_graph(g) {}

GraphType VariantGraph::HoldsType() const {
  if (std::holds_alternative<std::shared_ptr<const BasicGraph>>(m_graph)) {
    return GraphType::Undirected;
  } else if (std::holds_alternative<std::shared_ptr<const BasicDigraph>>(
                 m_graph)) {
    return GraphType::Directed;
  }
  estd::require(false, "VariantGraph is empty", "VariantGraph::HoldsType()");
  // The return value here is just to silence the compiler warnings.
  return GraphType::Directed;
}

bool VariantGraph::IsUndirected() const {
  return HoldsType() == GraphType::Undirected;
}

std::shared_ptr<const BasicGraph> VariantGraph::Undirected() const {
  return std::get<std::shared_ptr<const BasicGraph>>(m_graph);
}

bool VariantGraph::IsDirected() const {
  return HoldsType() == GraphType::Directed;
}

std::shared_ptr<const BasicDigraph> VariantGraph::Directed() const {
  return std::get<std::shared_ptr<const BasicDigraph>>(m_graph);
}

} // namespace graphsource
} // namespace graphbase
