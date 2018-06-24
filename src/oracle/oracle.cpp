#include "oracle/oracle.hpp"

#include <type_traits>

#include "graph/algo/bipartite.hpp"
#include "graphsource/graphsource.hpp"

using graphbase::graphsource::VariantGraph;

namespace graphbase {

void Oracle::RegisterSource(Kind source_kind,
                            std::unique_ptr<GraphSource> source) {
  estd::require(m_sources.find(source_kind) == std::end(m_sources),
                "one source kind registered twice", "Oracle::RegisterSource()");

  m_sources[source_kind] = std::move(source);
}

estd::generator<std::shared_ptr<const BasicGraph>>
Oracle::GetUndirectedGraphs(Kind source_kind,
                            std::shared_ptr<const Predicate> p) const {
  auto candidates = m_sources.at(source_kind)->Graphs();

  auto f = [candidates = std::move(candidates),
            p]() mutable -> std::optional<std::shared_ptr<const BasicGraph>> {
    std::optional<VariantGraph> opt_g;
    while ((opt_g = candidates.next())) {
      const auto &g = std::move(opt_g).value();
      if (p->Test(g)) {
        return g.Undirected();
      }
    }
    return std::nullopt;
  };
  return estd::generator<std::shared_ptr<const BasicGraph>>(std::move(f));
}

estd::generator<size_t>
Oracle::GetUndirectedGraphsCount(Kind source_kind,
                                 std::shared_ptr<const Predicate> p) const {
  size_t count = 0;

  auto graphs = GetUndirectedGraphs(source_kind, p);
  while (graphs.next()) {
    count++;
  }

  return estd::generator<size_t>::singleton(count);
}

} // namespace graphbase
