#include "third_party/catch.hpp"

#include <set>

#include "graph/graph/undirected.hpp"

using namespace graphbase;

using graph::edge_t;
using graph::undirected::BasicGraph;

void check_graph(const BasicGraph &g, const std::vector<edge_t> &want_edges,
                 const size_t graph_size) {
  // This function works only if there are no loops because when counting the
  // edges we are assuming that they are double counted because we are
  // iterating over edges adjacent to vertices. This is not true for loops as a
  // loop is counted only once at it "has only one endpoint".
  SECTION("Checking sizes") {
    REQUIRE(g.vertices().size() == graph_size);
    REQUIRE(g.edges().size() == want_edges.size());

    auto sum_size = 0;
    for (auto v : g.vertices()) {
      sum_size += g.edges().adjacent(v).size();
    }
    REQUIRE(sum_size / 2 == want_edges.size());
  }

  SECTION("Checking whether we have all the wanted vertices") {
    auto vertices = g.vertices();
    for (size_t v = 0; v < graph_size; v++) {
      REQUIRE(std::find(begin(vertices), end(vertices), v) != end(vertices));
    }
  }

  SECTION("Checking whether we have all the wanted edges") {
    for (const auto &e : want_edges) {
      const auto &edges_first = g.edges().adjacent(e.first());
      REQUIRE(std::find(begin(edges_first), end(edges_first), e) !=
              end(edges_first));

      const auto &edges_last = g.edges().adjacent(e.last());
      REQUIRE(std::find(begin(edges_last), end(edges_last), e) !=
              end(edges_last));
    }
  }

  SECTION("Counting all the edges by putting them in a set") {
    std::set<std::pair<unsigned, unsigned>> want_edges_set;
    for (const auto &e : want_edges) {
      auto p = static_cast<std::pair<unsigned, unsigned>>(e);
      want_edges_set.insert(p);
    }

    std::set<std::pair<unsigned, unsigned>> got_edges_set;
    g.for_each_edge([&got_edges_set](const edge_t &e) {
      auto p = static_cast<std::pair<unsigned, unsigned>>(e);
      got_edges_set.insert(p);
    });

    REQUIRE(want_edges_set == got_edges_set);
  }
}

TEST_CASE("Basic graph creation.", "[undirected] [graph]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 1), edge_t(1, 2), edge_t(1, 3),
      edge_t(2, 3), edge_t(3, 4), edge_t(4, 0),
  };

  // Expectations
  const auto &want_edges = edges;

  // Test
  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.add_edge(e);
  }

  // Assertions
  check_graph(g, want_edges, GRAPH_SIZE);
}

TEST_CASE("Basic (const) graph creation.", "[undirected] [graph]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 1), edge_t(1, 2), edge_t(1, 3),
      edge_t(2, 3), edge_t(3, 4), edge_t(4, 0),
  };

  // Expectations
  const auto &want_edges = edges;

  // Test
  auto raw_g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    raw_g.add_edge(e);
  }
  const auto &g = raw_g;

  // Assertions
  check_graph(g, want_edges, GRAPH_SIZE);
}

TEST_CASE("Removing adjacent edges", "[undirected] [graph]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 1), edge_t(1, 2), edge_t(1, 3),
      edge_t(2, 3), edge_t(3, 4), edge_t(4, 0),
  };
  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.add_edge(e);
  }

  // Expectations
  std::vector<edge_t> want_edges{
      // REMOVED: edge_t(0, 1),
      // REMOVED: edge_t(1, 2),
      // REMOVED: edge_t(1, 3),
      edge_t(2, 3),
      edge_t(3, 4),
      edge_t(4, 0),
  };

  // Test
  g.remove_adjacent_edges(1);

  // Assertions
  check_graph(g, want_edges, GRAPH_SIZE);
}

TEST_CASE("Removing edges", "[undirected] [graph]") {
  // Setup
  const size_t GRAPH_SIZE = 5;
  std::vector<edge_t> edges{
      edge_t(0, 1), edge_t(1, 2), edge_t(1, 3),
      edge_t(2, 3), edge_t(3, 4), edge_t(4, 0),
  };
  auto g = BasicGraph(GRAPH_SIZE);
  for (auto e : edges) {
    g.add_edge(e);
  }

  // Expectations
  std::vector<edge_t> want_edges{
      edge_t(0, 1),
      edge_t(1, 2),
      // REMOVED: edge_t(1, 3),
      edge_t(2, 3),
      // REMOVED: edge_t(3, 4),
      edge_t(4, 0),
  };

  // Test
  g.remove_edge(edge_t(1, 3));
  g.remove_edge(edge_t(3, 4));

  // Assertions
  check_graph(g, want_edges, GRAPH_SIZE);
}
