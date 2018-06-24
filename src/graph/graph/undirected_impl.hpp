#pragma once

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace graphbase {
namespace graph {
namespace undirected {

////////////////////////////////////////////////////////////////////////////////
// Implementation of an undirected graph with no data on vertices.
template <class EdgeContainer>
Graph<void, EdgeContainer>::Graph(size_t n) : m_edges(n) {
  m_vertices.reserve(n);
  for (size_t v = 0; v < n; v++) {
    m_vertices.push_back(v);
  }
}

template <class EdgeContainer>
const EdgeContainer &Graph<void, EdgeContainer>::edges() const {
  return m_edges;
}

template <class EdgeContainer>
EdgeContainer &Graph<void, EdgeContainer>::edges() {
  return m_edges;
}

template <class EdgeContainer>
const std::vector<unsigned> &Graph<void, EdgeContainer>::vertices() const {
  return m_vertices;
}

} // namespace undirected
} // namespace graph
} // namespace graphbase
