#include "graphsource/all_graphs.hpp"

#include <memory>

namespace graphbase {
namespace undirected {

///////////////////////////////////////////////////////////////////////////////
// IncrementableBigNum implementation
IncrementableBigNum::IncrementableBigNum(size_t n) : m_mask(n, false) {}

bool IncrementableBigNum::inc() {
  auto it = std::begin(m_mask);
  while (it != std::end(m_mask)) {
    if (*it == false) {
      *it = true;
      return true;
    }
    *it = false;
    it++;
  }
  return false;
}

const std::vector<bool> &IncrementableBigNum::vec() const { return m_mask; }

///////////////////////////////////////////////////////////////////////////////
// OfSize implementation
using graph::edge_t;
using graph::undirected::BasicGraph;

OfSize::OfSize(size_t n) : m_graphsize(n), m_mask(n * (n - 1) / 2) {}

std::optional<std::shared_ptr<BasicGraph>> OfSize::operator()() {
  bool successfully_incremented = m_mask.inc();
  if (not successfully_incremented) {
    return std::nullopt;
  }

  // This could be optimized in a lot of different ways.
  // 1. Allocate the graph only once.
  // 2. Keep the last graph and use a graph modyfying method (e.g. generate
  // the edge sets using a Hamiltonian walk on hypercube graph to change the
  // graph by just one edge.
  auto g = std::make_shared<BasicGraph>(m_graphsize);
  size_t edge_index = 0;
  for (unsigned first = 0; first < m_graphsize - 1; first++) {
    for (unsigned last = first + 1; last < m_graphsize; last++, edge_index++) {
      if (m_mask.vec()[edge_index]) {
        g->edges().add(edge_t(first, last));
      }
    }
  }
  return g;
}

///////////////////////////////////////////////////////////////////////////////
// OfSizeSource implementation
OfSizeSource::OfSizeSource(size_t n) : m_size(n) {}

// For some reason, clangformat cannot format these lines properly. It adds
// some weird "// namespace FOO" comments in the middle.
// clang-format off
estd::generator<VariantGraph> OfSizeSource::Graphs() const {
  std::function<std::optional<VariantGraph>()> f =
      [gen = std::make_shared<OfSize>(m_size)]() mutable -> std::optional<VariantGraph> {
        auto g = (*gen)();
        if (g) {
          return std::optional<VariantGraph>(*g);
        }
        return std::nullopt;
      };
  return estd::generator(std::move(f));
}
// clang-format on

Kind OfSizeSource::SourceKind() const { return Kind::All; }

graph::GraphType OfSizeSource::SourceGraphType() const {
  return graph::GraphType::Undirected;
}

}  // namespace undirected
}  // namespace graphbase
