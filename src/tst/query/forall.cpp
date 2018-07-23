#include "third_party/catch.hpp"

#include "query/evaluate.hpp"
#include "query/forall.hpp"
#include "query/list.hpp"
#include "query/var.hpp"
#include "query/logic.hpp"

using namespace query;

using Vec = std::vector<std::shared_ptr<const IExpression>>;

TEST_CASE("ForAll({'a': {False}}, True) == true", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(Vec{False::build()})),
      True::build());

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll({'a': {True, True}}, 'a') == true", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(Vec{
          True::build(),
          True::build()
          })),
      True::build());

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll({'a': {True, False}}, 'a') == false", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(Vec{
          True::build(),
          False::build()
          })),
      Var::build("a"));

  REQUIRE(not evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll environment extension (ForAll(a in {True, False}, ForAll(b in {True, True})) = a", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(
        std::string("a"),
        List::build(Vec{True::build(), False::build()})),
      ForAll::build(
        QuantifierBind::build(
          std::string("b"),
          List::build(Vec{True::build(), True::build()})),
        Var::build("a"))
      );

  REQUIRE(not evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll environment extension (ForAll(a in {True, False}, ForAll(b in {True, True})) = b", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(
        std::string("a"),
        List::build(Vec{True::build(), False::build()})),
      ForAll::build(
        QuantifierBind::build(
          std::string("b"),
          List::build(Vec{True::build(), True::build()})),
        Var::build("b"))
      );

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll environment shadowing (ForAll(a in {True, False}, ForAll(a in {True, True}, a))", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(
        std::string("a"),
        List::build(Vec{True::build(), False::build()})),
      ForAll::build(
        QuantifierBind::build(
          std::string("a"),
          List::build(Vec{True::build(), True::build()})),
        Var::build("a"))
      );

  REQUIRE(evaluate<bool>(env, *e).value());
}
