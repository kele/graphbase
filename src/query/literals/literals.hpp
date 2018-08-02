#pragma aonce

#include "estd/estd.hpp"

#include "query/environment.hpp"
#include "query/iexpression.hpp"
#include "query/value/value.hpp"

namespace query {
namespace literals {

struct Integer : public IExpression, public estd::shared<Integer> {
  Integer(int v) : value(v) {}

  value::Value eval(std::shared_ptr<const Environment> env) const final {
    return value::Value::of(value::Integer(value));
  }

  const int value;
};

class Boolean : public IExpression, public estd::shared<Boolean> {
public:
  Boolean(bool v) : value(v) {}
  value::Value eval(std::shared_ptr<const Environment> env) const final {
    return value::Value::of<value::Boolean>(value);
  }

  bool value;
};

} // namespace literals
} // namespace query
