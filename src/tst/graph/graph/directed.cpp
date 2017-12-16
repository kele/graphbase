// TODO(not ready yet)
//#include "third_party/catch.hpp"
//
//#include "graph/graph/directed.hpp"
//
// using namespace graphbase;
//
// using graph::arc_t;
// using graph::directed::BasicDigraph;
// using graph::directed::Digraph;
//
// TEST_CASE("Basic digraph creation.", "[directed] [graph]") {
//  // Setup
//  const size_t GRAPH_SIZE = 5;
//  std::vector<arc_t> arcs{
//      arc_t(0, 1), arc_t(1, 2), arc_t(1, 3),
//      arc_t(2, 3), arc_t(3, 4), arc_t(4, 0),
//  };
//
//  // Expectations
//  const auto &want_arcs = arcs;
//  std::vector<std::vector<arc_t>> want_outgoing{
//      {arc_t(0, 1)},               // 0
//      {arc_t(1, 2), arc_t(1, 3)},  // 1
//      {arc_t(2, 3)},               // 2
//      {arc_t(3, 4)},               // 3
//      {arc_t(4, 0)},               // 4
//  };
//
//  // Test
//  auto g = BasicDigraph(GRAPH_SIZE);
//  for (auto arc : arcs) {
//    // This is fine as arc is a POD.
//    g.add_arc(std::move(arc));
//  }
//
//  // Assertions
//  SECTION("Checking size of returned arc collections") {
//    REQUIRE(g.size() == GRAPH_SIZE);
//    REQUIRE(g.num_arcs() == want_arcs.size());
//    REQUIRE(g.arcs().size() == want_arcs.size());
//  }
//
//  SECTION("Checking whether we have all the wanted arcs") {
//    for (const auto &arc : want_arcs) {
//      auto got = g.find_arc(arc.first(), arc.last());
//      REQUIRE(got);
//      REQUIRE((*got)->first() == arc.first());
//      REQUIRE((*got)->last() == arc.last());
//    }
//  }
//  SECTION("Checking the output of outgoing_arcs()") {
//    for (unsigned i = 0; i < GRAPH_SIZE; i++) {
//      INFO("Looking at outgoing arcs from " << i);
//      const auto &got = g.outgoing_arcs(i);
//      const auto &want = want_outgoing[i];
//
//      REQUIRE(got.size() == want.size());
//      if (got.size() != want.size()) continue;
//
//      for (const auto &want_arc : want) {
//        REQUIRE(
//            std::find_if(begin(got), end(got), [&want_arc](const arc_t &arc) {
//              return want_arc.first() == arc.first() &&
//                     want_arc.last() == arc.last();
//            }) != end(got));
//      }
//    }
//  }
//}
//
// TEST_CASE("Basic (const) digraph creation.", "[directed] [graph]") {
//  // Setup
//  const size_t GRAPH_SIZE = 5;
//  std::vector<arc_t> arcs{
//      arc_t(0, 1), arc_t(1, 2), arc_t(1, 3),
//      arc_t(2, 3), arc_t(3, 4), arc_t(4, 0),
//  };
//
//  // Expectations
//  const auto &want_arcs = arcs;
//  std::vector<std::vector<arc_t>> want_outgoing{
//      {arc_t(0, 1)},               // 0
//      {arc_t(1, 2), arc_t(1, 3)},  // 1
//      {arc_t(2, 3)},               // 2
//      {arc_t(3, 4)},               // 3
//      {arc_t(4, 0)},               // 4
//  };
//
//  // Test
//  auto raw_g = BasicDigraph(GRAPH_SIZE);
//  for (auto arc : arcs) {
//    // This is fine as arc is a POD.
//    raw_g.add_arc(std::move(arc));
//  }
//
//  const auto &g = raw_g;
//
//  // Assertions
//  SECTION("Checking size of returned arc collections") {
//    REQUIRE(g.size() == GRAPH_SIZE);
//    REQUIRE(g.num_arcs() == want_arcs.size());
//    REQUIRE(g.arcs().size() == want_arcs.size());
//  }
//
//  SECTION("Checking whether we have all the wanted arcs") {
//    for (const auto &arc : want_arcs) {
//      auto got = g.find_arc(arc.first(), arc.last());
//      REQUIRE(got);
//      REQUIRE((*got)->first() == arc.first());
//      REQUIRE((*got)->last() == arc.last());
//    }
//  }
//  SECTION("Checking the output of outgoing_arcs()") {
//    for (unsigned i = 0; i < GRAPH_SIZE; i++) {
//      INFO("Looking at outgoing arcs from " << i);
//      const auto &got = g.outgoing_arcs(i);
//      const auto &want = want_outgoing[i];
//
//      REQUIRE(got.size() == want.size());
//      if (got.size() != want.size()) continue;
//
//      for (const auto &want_arc : want) {
//        REQUIRE(
//            std::find_if(begin(got), end(got), [&want_arc](const arc_t &arc) {
//              return want_arc.first() == arc.first() &&
//                     want_arc.last() == arc.last();
//            }) != end(got));
//      }
//    }
//  }
//}
//
// TEST_CASE("Removing outgoing arcs", "[directed] [graph]") {
//  // Setup
//  const size_t GRAPH_SIZE = 5;
//  std::vector<arc_t> arcs{
//      arc_t(0, 1), arc_t(1, 2), arc_t(1, 3),
//      arc_t(2, 3), arc_t(3, 4), arc_t(4, 0),
//  };
//  auto g = BasicDigraph(GRAPH_SIZE);
//  for (auto arc : arcs) {
//    // This is fine as arc is a POD.
//    g.add_arc(std::move(arc));
//  }
//
//  // Expectations
//  std::vector<arc_t> want_arcs{
//      arc_t(0, 1),
//      // REMOVED: arc_t(1, 2),
//      // REMOVED: arc_t(1, 3),
//      arc_t(2, 3),
//      arc_t(3, 4),
//      arc_t(4, 0),
//  };
//  std::vector<std::vector<arc_t>> want_outgoing{
//      {arc_t(0, 1)},  // 0
//      {},             // REMOVED: {arc_t(1, 2), arc_t(1, 3)},  // 1
//      {arc_t(2, 3)},  // 2
//      {arc_t(3, 4)},  // 3
//      {arc_t(4, 0)},  // 4
//  };
//
//  // Test
//  g.remove_outgoing_arcs(1);
//
//  // Assertions
//  SECTION("Checking size of returned arc collections") {
//    REQUIRE(g.size() == GRAPH_SIZE);
//    REQUIRE(g.num_arcs() == want_arcs.size());
//    REQUIRE(g.arcs().size() == want_arcs.size());
//  }
//
//  SECTION("Checking whether we have all the wanted arcs") {
//    for (const auto &arc : want_arcs) {
//      auto got = g.find_arc(arc.first(), arc.last());
//      REQUIRE(got);
//      REQUIRE((*got)->first() == arc.first());
//      REQUIRE((*got)->last() == arc.last());
//    }
//  }
//  SECTION("Checking the output of outgoing_arcs()") {
//    for (unsigned i = 0; i < GRAPH_SIZE; i++) {
//      INFO("Looking at outgoing arcs from " << i);
//      const auto &got = g.outgoing_arcs(i);
//      const auto &want = want_outgoing[i];
//
//      REQUIRE(got.size() == want.size());
//      if (got.size() != want.size()) continue;
//
//      for (const auto &want_arc : want) {
//        REQUIRE(
//            std::find_if(begin(got), end(got), [&want_arc](const arc_t &arc) {
//              return want_arc.first() == arc.first() &&
//                     want_arc.last() == arc.last();
//            }) != end(got));
//      }
//    }
//  }
//}
//
// TEST_CASE("Adding loops and multiple arcs between same vertices",
//          "[directed] [graph]") {
//  // Setup
//  const size_t GRAPH_SIZE = 5;
//  std::vector<arc_t> arcs{
//      arc_t(0, 0),
//      arc_t(0, 1),
//      arc_t(1, 2),
//      arc_t(1, 2),
//  };
//  auto g = BasicDigraph(GRAPH_SIZE);
//
//  // Expectations
//  std::vector<arc_t> want_arcs{
//      arc_t(0, 0),
//      arc_t(0, 1),
//      arc_t(1, 2),
//      arc_t(1, 2),
//  };
//  std::vector<std::vector<arc_t>> want_outgoing{
//      {arc_t(0, 0), arc_t(0, 1)},  // 0
//      {arc_t(1, 2), arc_t(1, 2)},  // 1
//      {},                          // 2
//      {},                          // 3
//      {},                          // 4
//  };
//
//  // Test
//  for (auto arc : arcs) {
//    // This is fine as arc is a POD.
//    g.add_arc(std::move(arc));
//  }
//
//  // Assertions
//  SECTION("Checking size of returned arc collections") {
//    REQUIRE(g.size() == GRAPH_SIZE);
//    REQUIRE(g.num_arcs() == want_arcs.size());
//    REQUIRE(g.arcs().size() == want_arcs.size());
//  }
//
//  SECTION("Checking whether we have all the wanted arcs") {
//    for (const auto &arc : want_arcs) {
//      auto got = g.find_arc(arc.first(), arc.last());
//      REQUIRE(got);
//      REQUIRE((*got)->first() == arc.first());
//      REQUIRE((*got)->last() == arc.last());
//    }
//  }
//  SECTION("Checking the output of outgoing_arcs()") {
//    for (unsigned i = 0; i < GRAPH_SIZE; i++) {
//      INFO("Looking at outgoing arcs from " << i);
//      const auto &got = g.outgoing_arcs(i);
//      const auto &want = want_outgoing[i];
//
//      REQUIRE(got.size() == want.size());
//      if (got.size() != want.size()) continue;
//
//      for (const auto &want_arc : want) {
//        REQUIRE(
//            std::find_if(begin(got), end(got), [&want_arc](const arc_t &arc) {
//              return want_arc.first() == arc.first() &&
//                     want_arc.last() == arc.last();
//            }) != end(got));
//      }
//    }
//  }
//}
//
// class weighted_arc_t : public arc_t {
// public:
//  weighted_arc_t(unsigned first, unsigned last, unsigned weight)
//      : arc_t(first, last), weight(weight) {}
//  unsigned weight;
//};
//
// TEST_CASE("Multiple arcs with different metadata", "[directed] [graph]") {
//  // Setup
//  const size_t GRAPH_SIZE = 5;
//  std::vector<weighted_arc_t> arcs{
//      weighted_arc_t(1, 2, 100),
//      weighted_arc_t(1, 2, 201),
//      weighted_arc_t(1, 2, 302),
//  };
//  auto g = Digraph<weighted_arc_t>(GRAPH_SIZE);
//
//  // Expectations
//  std::vector<weighted_arc_t> want_arcs{
//      weighted_arc_t(1, 2, 100),
//      weighted_arc_t(1, 2, 201),
//      weighted_arc_t(1, 2, 302),
//  };
//  std::vector<std::vector<weighted_arc_t>> want_outgoing{
//      {},  // 0
//      {weighted_arc_t(1, 2, 100), weighted_arc_t(1, 2, 201),
//       weighted_arc_t(1, 2, 302)},  // 1
//      {},                           // 2
//      {},                           // 3
//      {},                           // 4
//  };
//
//  // Test
//  for (auto arc : arcs) {
//    // This is fine as arc is a POD.
//    g.add_arc(std::move(arc));
//  }
//
//  // Assertions
//  SECTION("Checking size of returned arc collections") {
//    REQUIRE(g.size() == GRAPH_SIZE);
//    REQUIRE(g.num_arcs() == want_arcs.size());
//    REQUIRE(g.arcs().size() == want_arcs.size());
//  }
//
//  SECTION("Checking whether we have all the wanted arcs") {
//    for (const auto &arc : want_arcs) {
//      auto got = g.find_arc(arc.first(), arc.last());
//      REQUIRE(got);
//      REQUIRE((*got)->first() == arc.first());
//      REQUIRE((*got)->last() == arc.last());
//      // Weight cannot be checked here as find_arc doesn't guarantee which arc
//      // is going to be returned.
//    }
//  }
//
//  SECTION(
//      "Checking whether we have all the wanted arcs using arcs() (this allows
//      " "to check for metadata)") {
//    for (unsigned i = 0; i < GRAPH_SIZE; i++) {
//      INFO("Checking if outgoing arcs from " << i
//                                             << " are in the set of all
//                                             arcs");
//      const auto &want = want_outgoing[i];
//
//      const auto &got = g.arcs();
//      for (const auto &want_arc : want) {
//        REQUIRE(std::find_if(begin(got), end(got),
//                             [&want_arc](const weighted_arc_t &arc) {
//                               return want_arc.first() == arc.first() &&
//                                      want_arc.last() == arc.last() &&
//                                      want_arc.weight == arc.weight;
//                             }) != end(got));
//      }
//    }
//  }
//
//  SECTION("Checking the output of outgoing_arcs()") {
//    for (unsigned i = 0; i < GRAPH_SIZE; i++) {
//      INFO("Looking at outgoing arcs from " << i);
//      const auto &got = g.outgoing_arcs(i);
//      const auto &want = want_outgoing[i];
//
//      REQUIRE(got.size() == want.size());
//      if (got.size() != want.size()) continue;
//
//      for (const auto &want_arc : want) {
//        REQUIRE(std::find_if(begin(got), end(got),
//                             [&want_arc](const weighted_arc_t &arc) {
//                               return want_arc.first() == arc.first() &&
//                                      want_arc.last() == arc.last() &&
//                                      want_arc.weight == arc.weight;
//                             }) != end(got));
//      }
//    }
//  }
//}
