#include "third_party/catch.hpp"

#include "query/literals/literals.hpp"
#include "query/quantifier_bind.hpp"
#include "query/list.hpp"
#include "query/environment.hpp"
#include "query/logic.hpp"

using namespace query;

using query::literals::Boolean;

using Vec = std::vector<std::shared_ptr<const IExpression>>;

TEST_CASE("Quantifier Bind with a singleton", "[quantifier bind]") {
  auto env = std::make_shared<Environment>();
  auto qb = QuantifierBind::build("a", List::build(Vec{Boolean::build(true)}));

  auto g = qb->iterate(env);
  auto res = g->next();
  REQUIRE(res.has_value());
  auto binding = *res;
  REQUIRE(binding.find("a") != binding.end());
  // TODO: check the actual value

  REQUIRE(not g->next().has_value());
}

TEST_CASE("Quantifier Bind with a list", "[quantifier bind]") {
  auto env = std::make_shared<Environment>();
  auto list = List::build(Vec{Boolean::build(true), Boolean::build(true)});
  auto qb = QuantifierBind::build("a", list);

  REQUIRE(list->values().size() == 2);

  auto g = qb->iterate(env);
  auto res = g->next();
  REQUIRE(res.has_value());
  auto binding = *res;
  REQUIRE(binding.find("a") != binding.end());

  auto res2 = g->next();
  REQUIRE(res.has_value());
  binding = *res2;
  REQUIRE(binding.find("a") != binding.end());
  // TODO: check the actual value

  REQUIRE(not g->next().has_value());
}
