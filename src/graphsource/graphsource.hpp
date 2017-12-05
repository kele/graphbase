#pragma once

#include <memory>
#include <typeindex>
#include <variant>

#include "estd/estd.hpp"
#include "graph/graph/directed.hpp"
#include "graph/graph/undirected.hpp"
#include "graphsource/kinds.hpp"

namespace graphbase {
namespace graphsource {

using graph::GraphType;
using graph::directed::BasicDigraph;
using graph::undirected::BasicGraph;

// VariantGraph is a wrapper around a directed or undirected graph.
class VariantGraph {
 public:
  // TODO: maybe use unique_ptr?
  explicit VariantGraph(std::shared_ptr<const BasicGraph> g) : m_graph(g) {}
  explicit VariantGraph(std::shared_ptr<const BasicDigraph> g) : m_graph(g) {}

  GraphType HoldsType() const {
    if (std::holds_alternative<std::shared_ptr<const BasicGraph>>(m_graph)) {
      return GraphType::Undirected;
    } else if (std::holds_alternative<std::shared_ptr<const BasicDigraph>>(
                   m_graph)) {
      return GraphType::Directed;
    }
    estd::require(false, "VariantGraph is empty");
  }

  bool IsUndirected() const { return HoldsType() == GraphType::Undirected; }
  std::shared_ptr<const BasicGraph> Undirected() const {
    return std::get<std::shared_ptr<const BasicGraph>>(m_graph);
  }

  bool IsDirected() const {
    return HoldsType() == GraphType::Directed;
    ;
  }
  std::shared_ptr<const BasicDigraph> Directed() const {
    return std::get<std::shared_ptr<const BasicDigraph>>(m_graph);
  }

 private:
  std::variant<std::shared_ptr<const BasicDigraph>,
               std::shared_ptr<const BasicGraph>>
      m_graph;
};

class GraphSource {
 public:
  virtual estd::Generator<VariantGraph> Graphs() const = 0;
  virtual Kind SourceKind() const = 0;
  virtual GraphType SourceGraphType() const = 0;
};

}  // namespace graphsource
}  // namespace graphbase
