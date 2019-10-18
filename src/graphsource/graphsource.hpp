#pragma once

#include <memory>
#include <variant>

#include "estd/estd.hpp"
#include "estd/generator.hpp"
#include "graph/graph/directed.hpp"
#include "graph/graph/undirected.hpp"
#include "graphsource/kinds.hpp"

namespace graphbase {
namespace graphsource {

using graph::directed::BasicDigraph;
using undirected::BasicGraph;

// VariantGraph is a wrapper around a directed or undirected graph.
class VariantGraph {
public:
  explicit VariantGraph(std::shared_ptr<const BasicGraph> g);
  explicit VariantGraph(std::shared_ptr<const BasicDigraph> g);

  GraphType HoldsType() const;

  bool IsUndirected() const;

  bool IsDirected() const;

  std::shared_ptr<const BasicGraph> Undirected() const;

  std::shared_ptr<const BasicDigraph> Directed() const;

private:
  std::variant<std::shared_ptr<const BasicDigraph>,
               std::shared_ptr<const BasicGraph>>
      m_graph;
};

// GraphSource creates generators for specific graph types.
template<class G>
class GraphSource {
public:
  using GraphType = G;

  virtual estd::generator<GraphType> Graphs() const = 0;
  virtual const std::string& Label() const = 0;
  virtual ~GraphSource() = 0;
};

} // namespace graphsource
} // namespace graphbase
