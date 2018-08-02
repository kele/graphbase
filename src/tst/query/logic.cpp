#include "third_party/catch.hpp"

#include "query/literals/literals.hpp"
#include "query/evaluate.hpp"
#include "query/environment.hpp"
#include "query/logic.hpp"

using namespace query;

using query::literals::Boolean;

TEST_CASE("Not inverts the boolean value", "[logic]") {
  auto env = std::make_shared<Environment>();
  REQUIRE(not evaluate<bool>(env, *Not::build(Boolean::build(true))).value());
  REQUIRE(evaluate<bool>(env, *Not::build(Boolean::build(false))).value());
}

TEST_CASE("Double not", "[logic]") {
  auto env = std::make_shared<Environment>();
  REQUIRE(evaluate<bool>(env, *Not::build(Not::build(Boolean::build(true)))).value());
  REQUIRE(not evaluate<bool>(env, *Not::build(Not::build(Boolean::build(false)))).value());
}
