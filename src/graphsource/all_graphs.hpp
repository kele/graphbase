#pragma once

#include <vector>

#include "graph/graph/undirected.hpp"
#include "graphsource/graphsource.hpp"

namespace graphbase {
namespace undirected {

// IncrementableBigNum is a bignum that starts at zero and can be incremented.
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

using graphbase::graph::undirected::BasicGraph;

// OfSize generates all undirected graphs of a given size. Note that the
// generated graphs are not unique in terms of isomorphism.
struct OfSize {
  explicit OfSize(size_t n);

  // Returns the next graph.
  std::optional<std::shared_ptr<BasicGraph>> operator()();

private:
  size_t m_graphsize;
  IncrementableBigNum m_mask;
};

using graphbase::graphsource::GraphSource;
using graphbase::graphsource::Kind;
using graphbase::graphsource::VariantGraph;

// OfSizeSource is a GraphSource implementation of the OfSize generator.
class OfSizeSource : public GraphSource {
public:
  explicit OfSizeSource(size_t n);

  // Creates a new graph generator.
  estd::generator<VariantGraph> Graphs() const override;

  Kind SourceKind() const override;
  graph::GraphType SourceGraphType() const override;

private:
  size_t m_size;
};

} // namespace undirected
} // namespace graphbase
