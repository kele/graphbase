#include "third_party/catch.hpp"

#include "query/evaluate.hpp"
#include "query/logic.hpp"
#include "query/literals/literals.hpp"

using namespace query;
using query::literals::Boolean;
using query::literals::Integer;

class HasCorrectPositivity {
public:
  using Args = std::tuple<value::Boolean, value::Integer>;
  value::Value call(bool expected_positive, int n) const {
    bool is_positive = n >= 0;
    return value::Value::of(is_positive == expected_positive);
  }
};

TEST_CASE("evaluate on a single expression", "[query::evaluate]") {
  // TODO(kele)
}


TEST_CASE("evaluate on a vector", "[query::evaluate]") {
  auto env = std::make_shared<Environment>();
  HasCorrectPositivity::Args args = evaluate<HasCorrectPositivity::Args>(env, std::vector<std::shared_ptr<const IExpression>>{
      Boolean::build(true), Integer::build(123)});
  auto [b, i] = args;
  REQUIRE(b == true);
  REQUIRE(i == 123);
}

//TEST_CASE("evaluate on a vector - throw on length mismatch", "[query::evaluate]") {
//  auto env = std::make_shared<Environment>();
//  HasCorrectPositivity::Args args = evaluate<HasCorrectPositivity::Args>(env, std::vector<std::shared_ptr<const IExpression>>{});
//  REQUIRE(std::get<0>(args) == 123);
//  REQUIRE(std::get<1>(args) == true);
//}
