#pragma once

#include "estd/estd.hpp"
#include "graph/common/common.hpp"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace graphbase {
namespace graph {
namespace directed {

/* Directed graph.
 *
 * The digraph is parametrized by the arc type, thus allowing the graph to have
 * any data associated to the edges.
 *
 * This implementation allows for loops and multiple arcs between the same
 * vertices.
 */
template <class Arc = arc_t>
class Digraph {
  // TODO(Not ready yet)
  // public:
  //  explicit Digraph(size_t n) : m_arcs(n), m_num_arcs(0) {}
  //
  //  /* Returns the number of vertices in the graph. */
  //  size_t size() const { return m_arcs.size(); }
  //
  //  /* Removes outgoing arcs. */
  //  void remove_outgoing_arcs(unsigned v) {
  //    m_num_arcs -= m_arcs[v].size();
  //    m_arcs[v].clear();
  //  }
  //
  //  /* Removes ingoing arcs. */
  //  void remove_ingoing_arcs(unsigned v) {
  //    for (auto &arcs : m_arcs) {
  //      auto it = remove_if(begin(arcs), end(arcs),
  //                          [v](const Arc &arc) { return arc.last() == v; });
  //      m_num_arcs -= distance(it, end(arcs));
  //      arcs.erase(it, end(arcs));
  //    }
  //  }
  //
  //  /* Returns all the arcs. */
  //  std::vector<estd::cref<Arc>> arcs() const {
  //    std::vector<estd::cref<Arc>> result;
  //    for_each_arc([&result](estd::cref<Arc> e) { result.push_back(e); });
  //    return result;
  //  }
  //
  //  /* Performs an operation on each arc */
  //  void for_each_arc(std::function<void(estd::ref<Arc>)> f) {
  //    for (auto &arcs : m_arcs) {
  //      for (auto &e : arcs) {
  //        f(estd::ref(e));
  //      }
  //    }
  //  }
  //
  //  /* Performs an operation on each arc */
  //  void for_each_arc(std::function<void(estd::cref<Arc>)> f) const {
  //    for (const auto &arcs : m_arcs) {
  //      for (const auto &e : arcs) {
  //        f(estd::cref(e));
  //      }
  //    }
  //  }
  //
  //  /* Finds an arc with given beginning and end. */
  //  std::optional<estd::cref<Arc>> find_arc(unsigned first, unsigned last)
  //  const {
  //    for (const auto &arcs : m_arcs) {
  //      for (const auto &arc : arcs) {
  //        if (arc.first() == first && arc.last() == last) {
  //          return estd::cref(arc);
  //        }
  //      }
  //    }
  //    return std::nullopt;
  //  }
  //
  //  /* Finds an arc with given beginning and end. */
  //  std::optional<estd::ref<Arc>> find_arc(unsigned first, unsigned last) {
  //    for (auto &arcs : m_arcs) {
  //      for (auto &arc : arcs) {
  //        if (arc.first() == first && arc.last() == last) {
  //          return estd::ref(arc);
  //        }
  //      }
  //    }
  //    return std::nullopt;
  //  }
  //
  //  /* Adds an arc to the graph. */
  //  void add_arc(Arc &&arc) {
  //    m_arcs[arc.first()].emplace_back(arc);
  //    m_num_arcs++;
  //  }
  //
  //  /* Removes an arc from the graph. */
  //  void remove_arc(unsigned u, unsigned v) {
  //    auto it = find_arc(u, v);
  //    if (it == m_arcs[u].end()) {
  //      std::stringstream ss;
  //      ss << "Edge (" << u << ", " << v << ") does not exist.";
  //      throw std::out_of_range(ss.str());
  //    }
  //    *it = m_arcs[u].back();
  //    m_arcs[u].pop_back();
  //
  //    m_num_arcs--;
  //  }
  //
  //  /* The number of arcs in the graph. */
  //  size_t num_arcs() const { return m_num_arcs; }
  //
  //  /* Outgoing arcs. */
  //  const std::vector<Arc> &outgoing_arcs(unsigned u) const { return
  //  m_arcs[u]; }
  //
  //  /* Outgoing arcs. */
  //  std::vector<Arc> &outgoing_arcs(unsigned u) { return m_arcs[u]; }
  //
  // private:
  //  std::vector<std::vector<Arc>> m_arcs;
  //  size_t m_num_arcs;
};

using BasicDigraph = Digraph<>;

}  // namespace directed
}  // namespace graph
}  // namespace graphbase
