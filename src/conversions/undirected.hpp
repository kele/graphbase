#pragma once

#include <sstream>

#include "graph/graph/undirected.hpp"

namespace graphbase {
namespace conversions {

// ToGraph6 returns the graph6 representation of an undirected graph.
std::string ToGraph6(const graph::undirected::BasicGraph &g);

} // namespace conversions
} // namespace graphbase
