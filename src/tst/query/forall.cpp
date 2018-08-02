#include "third_party/catch.hpp"

#include "query/evaluate.hpp"
#include "query/forall.hpp"
#include "query/list.hpp"
#include "query/literals/literals.hpp"
#include "query/logic.hpp"
#include "query/var.hpp"

using namespace query;
using literals::Boolean;

using Vec = std::vector<std::shared_ptr<const IExpression>>;

TEST_CASE("ForAll({'a': {False}}, True) == true", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(Vec{Boolean::build(false)})),
      Boolean::build(true));

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll({'a': {True, True}}, 'a') == true", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(Vec{
          Boolean::build(true),
          Boolean::build(true)
          })),
      Boolean::build(true));

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll({'a': {True, False}}, 'a') == false", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(std::string("a"), List::build(Vec{
          Boolean::build(true),
          Boolean::build(false)
          })),
      Var::build("a"));

  REQUIRE(not evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll environment extension (ForAll(a in {True, False}, ForAll(b in {True, True})) = a", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(
        std::string("a"),
        List::build(Vec{Boolean::build(true), Boolean::build(false)})),
      ForAll::build(
        QuantifierBind::build(
          std::string("b"),
          List::build(Vec{Boolean::build(true), Boolean::build(true)})),
        Var::build("a"))
      );

  REQUIRE(not evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll environment extension (ForAll(a in {True, False}, ForAll(b in {True, True})) = b", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(
        std::string("a"),
        List::build(Vec{Boolean::build(true), Boolean::build(false)})),
      ForAll::build(
        QuantifierBind::build(
          std::string("b"),
          List::build(Vec{Boolean::build(true), Boolean::build(true)})),
        Var::build("b"))
      );

  REQUIRE(evaluate<bool>(env, *e).value());
}

TEST_CASE("ForAll environment shadowing (ForAll(a in {True, False}, ForAll(a in {True, True}, a))", "[forall]") {
  auto env = std::make_shared<Environment>();
  auto e = ForAll::build(
      QuantifierBind::build(
        std::string("a"),
        List::build(Vec{Boolean::build(true), Boolean::build(false)})),
      ForAll::build(
        QuantifierBind::build(
          std::string("a"),
          List::build(Vec{Boolean::build(true), Boolean::build(true)})),
        Var::build("a"))
      );

  REQUIRE(evaluate<bool>(env, *e).value());
}
