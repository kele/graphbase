#include "third_party/catch.hpp"

#include "query/environment.hpp"
#include "query/value/value.hpp"
#include "query/logic.hpp"
#include "query/call.hpp"

using namespace query;

class IsFalse {
public:
  using Args = std::tuple<value::Boolean>;
  value::Value call(const Args& args) const {
    return value::Value::of(bool(!std::get<0>(args)));
  }
};

class IsSameBoolean {
public:
  using Args = std::tuple<value::Boolean, value::Boolean>;
  value::Value call(const Args& args) const {
    return value::Value::of(bool(std::get<0>(args) == std::get<1>(args)));
  }
};

TEST_CASE("A single arg builtin function and a call to it.", "[query::Call]") {
  auto env = std::make_shared<Environment>();

  Call<IsFalse> is_false_false{std::vector<std::shared_ptr<const IExpression>>{query::True::build()}};
  REQUIRE(false == is_false_false.eval(env).get<value::Boolean>());

  Call<IsFalse> is_false_true{std::vector<std::shared_ptr<const IExpression>>{query::False::build()}};
  REQUIRE(true == is_false_true.eval(env).get<value::Boolean>());
}

TEST_CASE("A many arg builtin function and a call to it.", "[query::Call]") {
  auto env = std::make_shared<Environment>();

  Call<IsSameBoolean> is_same_false{std::vector<std::shared_ptr<const IExpression>>{query::True::build(), query::False::build()}};
  REQUIRE(false == is_same_false.eval(env).get<value::Boolean>());

  Call<IsSameBoolean> is_same_true{std::vector<std::shared_ptr<const IExpression>>{query::True::build(), query::True::build()}};
  REQUIRE(true == is_same_true.eval(env).get<value::Boolean>());
}
