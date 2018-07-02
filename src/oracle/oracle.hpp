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
  estd::generator<std::shared_ptr<const BasicGraph>>
  GetUndirectedGraphs(Kind source_kind,
                      std::shared_ptr<const Predicate> p) const;
};

} // namespace graphbase
