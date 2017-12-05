#pragma once

#include <sstream>

#include "graph/graph/undirected.hpp"

namespace graphbase {
namespace conversions {

template<class G, class = graph::undirected::is_undirected_graph<G>>
std::string ToGraph6(const G& g) {
  // TODO: this is not actually graph6, but we'll stick with that for now
  std::stringstream ss;
  ss << "size: " << g.vertices().size() << " | ";
  g.for_each_edge([&ss](const graph::edge_t& e) {
    ss << "(" << e.first() << ", " << e.last() << ")";
  });
  return ss.str();
}

} // namespace conversions
} // namespace graphbase
