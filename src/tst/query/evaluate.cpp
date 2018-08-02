#include "third_party/catch.hpp"

#include "query/evaluate.hpp"

using namespace query;

class HasCorrectPositivity {
public:
  using Args = std::tuple<value::Boolean, value::Integer>;
  value::Value call(const Args& args) const {
    bool is_positive = std::get<1>(args) >= 0;
    return value::Value::of(value::Boolean(std::get<0>(args) == is_positive));
  }
};

TEST_CASE("evaluate on a single expression", "[query::evaluate]") {
  // TODO(kele)
}

TEST_CASE("evaluate on a vector", "[query::evaluate]") {
  // TODO(kele): we need to create literals first, lol
}
