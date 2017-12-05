#pragma once

namespace graphbase {
namespace graph {
namespace undirected {

template <class EdgeContainer>
Graph<void, EdgeContainer>::Graph(size_t n) : m_edges(n) {
  m_vertices.reserve(n);
  for (size_t v = 0; v < n; v++) {
    m_vertices.push_back(v);
  }
}

template <class EdgeContainer>
void Graph<void, EdgeContainer>::remove_adjacent_edges(unsigned v) {
  m_edges.remove_adjacent(v);
}

template <class EdgeContainer>
const EdgeContainer &Graph<void, EdgeContainer>::edges() const {
  return m_edges;
}

template <class EdgeContainer>
void Graph<void, EdgeContainer>::for_each_edge(
    std::function<void(const edge_t &)> f) const {
  m_edges.for_each(f);
}

template <class EdgeContainer>
void Graph<void, EdgeContainer>::add_edge(edge_t edge) {
  m_edges.add(edge);
}

template <class EdgeContainer>
void Graph<void, EdgeContainer>::remove_edge(edge_t edge) {
  m_edges.remove(edge);
}

template <class EdgeContainer>
const std::vector<unsigned> &Graph<void, EdgeContainer>::vertices() const {
  return m_vertices;
}

}  // namespace undirected
}  // namespace graph
}  // namespace graphbase
