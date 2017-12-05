#pragma once

#include <memory>

#include "estd/estd.hpp"
#include "graph/algo/bipartite.hpp"
#include "graph/algo/predicates.hpp"
#include "graph/graph/undirected.hpp"
#include "graphsource/graphsource.hpp"
#include "graphsource/kinds.hpp"
#include "protos/sv_oracle.pb.h"

namespace graphbase {

using graph::algo::Predicate;
using graph::undirected::BasicGraph;
using graphbase::graphsource::GraphSource;
using graphbase::graphsource::Kind;

class Oracle {
 public:
  void RegisterSource(Kind source_kind, std::unique_ptr<GraphSource> source);

  estd::Generator<std::shared_ptr<const BasicGraph>> GetUndirectedGraphs(
      Kind source_kind, std::shared_ptr<const Predicate> p) const;

  estd::Generator<size_t> GetUndirectedGraphsCount(
      Kind source_kind, std::shared_ptr<const Predicate> p) const;

 private:
  std::map<Kind, std::unique_ptr<GraphSource>> m_sources;
};

}  // namespace graphbase
