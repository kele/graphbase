#include "third_party/catch.hpp"

#include "query/environment.hpp"
#include "query/value/value.hpp"
#include "query/logic.hpp"
#include "query/literals/literals.hpp"
#include "query/call.hpp"

using namespace query;

using query::literals::Boolean;

class IsFalse {
public:
  using Args = std::tuple<value::Boolean>;
  value::Value call(bool arg) const {
    return value::Value::of(value::Boolean(arg == false));
  }
};

class IsSameBoolean {
public:
  using Args = std::tuple<value::Boolean, value::Boolean>;
  value::Value call(bool lhs, bool rhs) const {
    return value::Value::of(value::Boolean(lhs == rhs));
  }
};

TEST_CASE("A single arg builtin function and a call to it.", "[query::Call]") {
  auto env = std::make_shared<Environment>();

  Call<IsFalse> is_false_false{std::vector<std::shared_ptr<const IExpression>>{Boolean::build(true)}};
  REQUIRE(false == is_false_false.eval(env).get<value::Boolean>());

  Call<IsFalse> is_false_true{std::vector<std::shared_ptr<const IExpression>>{Boolean::build(false)}};
  REQUIRE(true == is_false_true.eval(env).get<value::Boolean>());
}

TEST_CASE("A many arg builtin function and a call to it.", "[query::Call]") {
  auto env = std::make_shared<Environment>();

  Call<IsSameBoolean> is_same_false{std::vector<std::shared_ptr<const IExpression>>{Boolean::build(true), Boolean::build(false)}};
  REQUIRE(false == is_same_false.eval(env).get<value::Boolean>());

  Call<IsSameBoolean> is_same_true{std::vector<std::shared_ptr<const IExpression>>{Boolean::build(true), Boolean::build(true)}};
  REQUIRE(true == is_same_true.eval(env).get<value::Boolean>());
}
