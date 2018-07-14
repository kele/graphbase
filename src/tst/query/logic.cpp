#include "third_party/catch.hpp"

#include "query/evaluate.hpp"
#include "query/environment.hpp"
#include "query/logic.hpp"

using namespace query;

TEST_CASE("True evalues to true", "[logic]") {
  auto env = std::make_shared<Environment>();
  REQUIRE(evaluate<bool>(env, *True::build()).value());
}

TEST_CASE("False evalues to false", "[logic]") {
  auto env = std::make_shared<Environment>();
  REQUIRE(not evaluate<bool>(env, *False::build()).value());
}

TEST_CASE("Not inverts the boolean value", "[logic]") {
  auto env = std::make_shared<Environment>();
  REQUIRE(not evaluate<bool>(env, *Not::build(True::build())).value());
  REQUIRE(evaluate<bool>(env, *Not::build(False::build())).value());
}

TEST_CASE("Double not", "[logic]") {
  auto env = std::make_shared<Environment>();
  REQUIRE(evaluate<bool>(env, *Not::build(Not::build(True::build()))).value());
  REQUIRE(not evaluate<bool>(env, *Not::build(Not::build(False::build()))).value());
}
