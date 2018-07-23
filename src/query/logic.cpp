#include "query/logic.hpp"
#include "estd/estd.hpp"
#include "query/evaluate.hpp"

namespace query {

// True
Value True::eval(std::shared_ptr<const Environment>) const {
  return Value::from<bool>(true);
}

// False
Value False::eval(std::shared_ptr<const Environment>) const {
  return Value::from<bool>(false);
}

// Not
Not::Not(std::shared_ptr<const IExpression> expr) : m_expr(std::move(expr)) {}

Value Not::eval(std::shared_ptr<const Environment> env) const {
  return Value::from<bool>(!evaluate<bool>(env, *m_expr).value());
}

} // namespace query
