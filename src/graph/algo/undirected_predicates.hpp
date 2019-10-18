#pragma once

#include "graph/algo/predicates.hpp"

namespace graphbase {
namespace undirected {
namespace predicates {

class IsBipartite : public graphbase::predicates::Predicate<BasicGraph> {
public:
  bool Test(const BasicGraph &g) const override;
};

} // namespace predicates
} // namespace undirected
} // namespace graphbase
