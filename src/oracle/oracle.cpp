#include "oracle/oracle.hpp"

#include <type_traits>
#include <map>
#include <optional>

#include "graph/algo/bipartite.hpp"
#include "graphsource/graphsource.hpp"

using graphbase::graphsource::VariantGraph;

namespace graphbase {

estd::generator<std::shared_ptr<const BasicGraph>>
Oracle::GetUndirectedGraphs(Kind source_kind,
                            std::shared_ptr<const Predicate> p) const {
  auto it = m_sources->find(source_kind);
  if (it == m_sources->begin()) {
    // TODO: handle it better
    throw std::runtime_error("Cannot find source.");
  }
  auto graphs = it->second->Graphs();
  auto gen = [graphs, p]() mutable -> std::optional<std::shared_ptr<const BasicGraph>> {
    for (auto opt = graphs.next(); opt.has_value(); opt = graphs.next()) {
      auto g = *opt;
      if (p->Test(g)) {
        return std::make_optional(g.Undirected());
      }
    }
    return std::nullopt;
  };
  return estd::generator<std::shared_ptr<const BasicGraph>>(gen);
}

} // namespace graphbase
