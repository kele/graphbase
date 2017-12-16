#include "third_party/catch.hpp"

#include "graph/algo/bipartite.hpp"
#include "graph/graph/undirected.hpp"

using namespace graphbase;

using graph::edge_t;
using graph::undirected::BasicGraph;
using graph::undirected::algo::IsBipartite;

TEST_CASE("Non bipartite graph", "[undirected] [graph] [bipartite]") {
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
  REQUIRE(not IsBipartite(g));
}

TEST_CASE("Bipartite graph", "[undirected] [graph] [bipartite]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 3), edge_t(0, 4), edge_t(1, 3),
      edge_t(1, 4), edge_t(2, 3), edge_t(2, 4),
  };

  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.edges().add(e);
  }

  // Test
  REQUIRE(IsBipartite(g));
}

TEST_CASE("Non bipartite, disconnected graph",
          "[undirected] [graph] [bipartite]") {
  // Setup
  const size_t GRAPH_SIZE = 8;
  std::vector<edge_t> edges{
      edge_t(0, 3),
      edge_t(0, 4),
      edge_t(1, 3),
      edge_t(1, 4),
      edge_t(2, 3),
      edge_t(2, 4),
      // Creating a clique between 5, 6, 7 that makes the graph non-bipartite
      edge_t(5, 6),
      edge_t(6, 7),
      edge_t(7, 5),
  };

  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.edges().add(e);
  }

  // Test
  REQUIRE(not IsBipartite(g));
}
