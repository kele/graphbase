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

using graph::predicates::Predicate;
using graph::undirected::BasicGraph;
using graphbase::graphsource::GraphSource;
using graphbase::graphsource::Kind;

class Oracle {
public:
  Oracle(std::unique_ptr<std::map<Kind, std::shared_ptr<GraphSource>>> sources) : m_sources(std::move(sources)) {}

  estd::generator<std::shared_ptr<const BasicGraph>>
  GetUndirectedGraphs(Kind source_kind,
                      std::shared_ptr<const Predicate> p) const;

protected:
  std::unique_ptr<std::map<Kind, std::shared_ptr<GraphSource>>> m_sources;
};

} // namespace graphbase
