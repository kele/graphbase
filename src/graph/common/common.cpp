#include "graph/common/common.hpp"

namespace graphbase {
namespace graph {

///////////////////////////////////////////////////////////////////////////////
// arc_t implementation
arc_t::arc_t(unsigned first, unsigned last) : m_first(first), m_last(last) {}

///////////////////////////////////////////////////////////////////////////////
// edge_t implementation
edge_t::edge_t(unsigned first, unsigned last) : m_e(first, last) {
  normalize();
}

// normalize normalizes the edge.
//
// (a, b) and (b, a) undirected edges are logically the same, so the make
// things simpler, each time a new edge_t is created, the vertices are saved in
// a manner that guarantees that the first vertex is not greater than the
// second one.
void edge_t::normalize() {
  if (m_e.first > m_e.second) {
    std::swap(m_e.first, m_e.second);
  }
}

edge_t::operator const std::pair<unsigned, unsigned> &() const { return m_e; }

bool operator==(const edge_t &lhs, const edge_t &rhs) {
  return lhs.m_e == rhs.m_e;
}

}  // namespace graph
}  // namespace graphbase
