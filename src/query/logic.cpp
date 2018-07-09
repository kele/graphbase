#include "query/logic.hpp"
#include "estd/estd.hpp"
#include "query/evaluate.hpp"

namespace query {

std::shared_ptr<True> True::build() {
  return std::make_shared<estd::enable_make_shared<True>>();
}

Value True::evalImpl(const Environment &env) const {
  return Value::from<bool>(true);
}

std::shared_ptr<False> False::build() {
  return std::make_shared<estd::enable_make_shared<False>>();
}

Value False::evalImpl(const Environment &env) const {
  return Value::from<bool>(false);
}

Not Not::build(const Environment &env, std::unique_ptr<Expression> expr) {
  // TODO: Typecheck.
  return Not(std::move(expr));
}

Not::Not(std::unique_ptr<Expression> expr) : m_expr(std::move(expr)) {}

Value Not::evalImpl(const Environment &env) const {
  return Value::from<bool>(evaluate<bool>(env, *m_expr).value());
}

} // namespace query
