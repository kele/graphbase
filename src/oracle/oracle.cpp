#include "oracle/oracle.hpp"

#include <type_traits>

#include "graph/algo/bipartite.hpp"
#include "graphsource/graphsource.hpp"

using graphbase::graphsource::VariantGraph;

namespace graphbase {

estd::generator<std::shared_ptr<const BasicGraph>>
Oracle::GetUndirectedGraphs(Kind source_kind,
                            std::shared_ptr<const Predicate> p) const {
  throw std::runtime_error("Not implemented.");
}

} // namespace graphbase
