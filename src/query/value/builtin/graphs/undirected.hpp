#pragma once

#include "graphsource/all_graphs.hpp"

namespace query {
namespace value {
namespace builtin {
namespace graphs {

class UndirectedGraphs : private graphbase::undirected::OfSize,
                         public patterns::IStream<std::unique_ptr<Value>> {
public:
  explicit UndirectedGraphs(size_t n) : m_size(n) {}
};

} // namespace graphs
} // namespace builtin
} // namespace value
} // namespace query
