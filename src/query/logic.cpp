#include "query/logic.hpp"
#include "estd/estd.hpp"
#include "query/evaluate.hpp"

namespace query {

using value::Value;

// Not
Not::Not(std::shared_ptr<const IExpression> expr) : m_expr(std::move(expr)) {}

Value Not::eval(std::shared_ptr<const Environment> env) const {
  return Value::of<value::Boolean>(
      !evaluate<value::Boolean>(env, *m_expr).value());
}

} // namespace query
