#pragma once

#include <vector>

#include "graph/graph/undirected.hpp"
#include "graphsource/graphsource.hpp"

// IncrementableBigNum is a bignum that starts at zero and can be incremented.
// TODO(kele): move it somewhere else
class IncrementableBigNum {
public:
  // Creates a bignum of `n` bits size.
  explicit IncrementableBigNum(size_t n);

  // Increments the bignum by one. Returns false if the bignum cannot be
  // incremented (all ones).
  bool inc();

  // Returns a big-endian representation of the bignum.
  const std::vector<bool> &vec() const;

private:
  std::vector<bool> m_mask;
};

namespace graphbase {

using BasicGraph = undirected::BasicGraph;

// OfSize generates all undirected graphs of a given size. Note that the
// generated graphs are not unique in terms of isomorphism.
template<class G>
struct OfSize {
  explicit OfSize(size_t n);

  // Returns the next graph.
  std::optional<std::shared_ptr<G>> operator()();

private:
  size_t m_graphsize;
  IncrementableBigNum m_mask;
};

// TODO(kele): move to _impl.hpp
template<>
OfSize<BasicGraph>::OfSize(size_t n) : m_graphsize(n), m_mask(n * (n - 1) / 2) {}

template<>
std::optional<std::shared_ptr<BasicGraph>> OfSize<BasicGraph>::operator()() {
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


namespace undirected {

using graphbase::undirected::BasicGraph;


using graphbase::graphsource::GraphSource;

///////////////////////////////////////////////////////////////////////////////
// OfSizeSource is a GraphSource implementation of the OfSize generator.
template<class G>
class OfSizeSource : public GraphSource<G> {
public:
  explicit OfSizeSource(size_t n);

  estd::generator<G> Graphs() const override;
  const std::string& Label() const override;

private:
  size_t m_size;
};

template<class G>
OfSizeSource<G>::OfSizeSource(size_t n) : m_size(n) {}

// For some reason, clangformat cannot format these lines properly. It adds
// some weird "// namespace FOO" comments in the middle.
// clang-format off
template<class G>
estd::generator<G> OfSizeSource<G>::Graphs() const {
  std::function<std::optional<G>()> f =
      [gen = std::make_shared<OfSize<G>>(m_size)]() mutable -> std::optional<G> {
        auto g = (*gen)();
        if (g) {
          return std::optional<G>(*g);
        }
        return std::nullopt;
      };
  return estd::generator(std::move(f));
}
// clang-format on

} // namespace undirected
} // namespace graphbase
