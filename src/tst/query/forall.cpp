#include "third_party/catch.hpp"

#include "query/evaluate.hpp"
#include "query/forall.hpp"
#include "query/list.hpp"
#include "query/logic.hpp"

using namespace query;

TEST_CASE("ForAll({'a': {False}}, True) == true", "[forall]") {
  Environment env;
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(std::vector<std::shared_ptr<const IExpression>>{False::build()})),
      True::build());

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll({'a': {True, True}}, 'a') == true", "[forall]") {
  Environment env;
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(std::vector<std::shared_ptr<const IExpression>>{
          True::build(),
          True::build()
          })),
      True::build());

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll({'a': {True, False}}, 'a') == false", "[forall]") {
  Environment env;
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(std::vector<std::shared_ptr<const IExpression>>{
          True::build(),
          False::build()
          })),
      True::build());

  REQUIRE(not evaluate<bool>(env, *e).value());
}
