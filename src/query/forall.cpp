#include "query/forall.hpp"
#include "query/environment.hpp"
#include "query/evaluate.hpp"
#include "query/quantifier_bind.hpp"

#include "query/logic.hpp"

namespace query {

std::shared_ptr<const ForAll>
ForAll::build(std::shared_ptr<const QuantifierBind> bind,
              std::shared_ptr<const IExpression> expr) {
  return std::make_shared<estd::enable_make_shared<ForAll>>(std::move(bind),
                                                            std::move(expr));
}

Value ForAll::evalImpl(const Environment &env) const {
  auto gen = m_bind->iterate(env);
  while (true) {
    auto opt_b = gen.next();
    if (not opt_b.has_value()) {
      break;
    }
    auto result = evaluate<bool>(Environment::extend(env, *opt_b), *m_expr);
    if (!result.has_value()) {
      throw std::logic_error("Cannot evaluate expression to true/false.");
    }
    if (!result.value()) {
      return Value::from<bool>(false);
    }
  }
  return Value::from<bool>(true);
}

ForAll::ForAll(std::shared_ptr<const QuantifierBind> bind,
               std::shared_ptr<const IExpression> expr)
    : m_bind(std::move(bind)), m_expr(std::move(expr)) {}

} // namespace query
