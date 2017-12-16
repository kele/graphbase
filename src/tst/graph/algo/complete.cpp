#include "third_party/catch.hpp"

#include "graph/algo/complete.hpp"
#include "graph/graph/undirected.hpp"

using namespace graphbase;

using graph::edge_t;
using graph::undirected::BasicGraph;
using graph::undirected::IsComplete;

TEST_CASE("Non complete graph", "[undirected] [graph] [complete]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 1), edge_t(1, 2), edge_t(1, 3),
      edge_t(2, 3), edge_t(3, 4), edge_t(4, 0),
  };

  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.edges().add(e);
  }

  // Test
  REQUIRE(not IsComplete(g));
}

TEST_CASE("Complete graph", "[undirected] [graph] [complete]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 1), edge_t(0, 2), edge_t(0, 3), edge_t(0, 4), edge_t(1, 2),
      edge_t(1, 3), edge_t(1, 4), edge_t(2, 3), edge_t(2, 4), edge_t(3, 4),
  };

  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.edges().add(e);
  }

  // Test
  REQUIRE(IsComplete(g));
}
