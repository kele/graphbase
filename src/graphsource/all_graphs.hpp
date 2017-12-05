#pragma once

#include <memory>
#include <vector>

#include "graphsource/graphsource.hpp"

namespace graphbase {
namespace undirected {

class IncrementableBigNum {
 public:
  explicit IncrementableBigNum(size_t n);
  bool inc();
  const std::vector<bool> &vec() const;

 private:
  std::vector<bool> m_mask;
};

using graphbase::graphsource::GraphSource;
using graphbase::graphsource::Kind;
using graphbase::graphsource::VariantGraph;

struct OfSize {
  explicit OfSize(size_t n);
  std::optional<VariantGraph> operator()();

 private:
  size_t m_graphsize;
  IncrementableBigNum m_mask;
};

class OfSizeSource : public GraphSource {
 public:
  explicit OfSizeSource(size_t n);

  estd::Generator<VariantGraph> Graphs() const override;
  Kind SourceKind() const override;
  graph::GraphType SourceGraphType() const override;

 private:
  size_t m_size;
};

}  // namespace undirected
}  // namespace graphbase
