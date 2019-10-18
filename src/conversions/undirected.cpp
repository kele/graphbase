#include "conversions/undirected.hpp"

#include <sstream>

namespace graphbase {
namespace conversions {

std::string ToGraph6(const undirected::BasicGraph &g) {
  // TODO: this is not actually graph6, but we'll stick with that for now
  std::stringstream ss;
  ss << "size: " << g.vertices().size() << " | ";
  g.edges().for_each([&ss](const edge_t &e) {
    ss << "(" << e.first() << ", " << e.last() << "), ";
  });
  return ss.str();
}

} // namespace conversions
} // namespace graphbase
