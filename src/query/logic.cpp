#include "query/logic.hpp"
#include "estd/estd.hpp"
#include "query/evaluate.hpp"

namespace query {

// True
std::shared_ptr<True> True::build() {
  return std::make_shared<estd::enable_make_shared<True>>();
}

Value True::eval(std::shared_ptr<const Environment>) const {
  return Value::from<bool>(true);
}

// False
std::shared_ptr<False> False::build() {
  return std::make_shared<estd::enable_make_shared<False>>();
}

Value False::eval(std::shared_ptr<const Environment>) const {
  return Value::from<bool>(false);
}

// Not
std::shared_ptr<Not> Not::build(std::shared_ptr<const IExpression> expr) {
  return std::make_shared<estd::enable_make_shared<Not>>(std::move(expr));
}

Not::Not(std::shared_ptr<const IExpression> expr) : m_expr(std::move(expr)) {}

Value Not::eval(std::shared_ptr<const Environment> env) const {
  return Value::from<bool>(!evaluate<bool>(env, *m_expr).value());
}

} // namespace query
