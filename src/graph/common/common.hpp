#pragma once

#include <utility>

namespace graphbase {
namespace graph {

enum class GraphType { Undirected, Directed };

// Directed arc (edge).
class arc_t {
public:
  arc_t(unsigned first, unsigned last);

  unsigned first() const { return m_first; }
  unsigned last() const { return m_last; }

  inline friend arc_t reverse(arc_t arc) {
    return arc_t{arc.last(), arc.first()};
  }

protected:
  unsigned m_first, m_last;
};

// Undirected edge.
class edge_t {
public:
  edge_t(unsigned first, unsigned last);

  unsigned first() const { return m_e.first; }
  unsigned last() const { return m_e.second; }

  operator const std::pair<unsigned, unsigned> &() const;

  friend bool operator==(const edge_t &lhs, const edge_t &rhs);

protected:
  std::pair<unsigned, unsigned> m_e;

private:
  void normalize();
};

} // namespace graph
} // namespace graphbase
