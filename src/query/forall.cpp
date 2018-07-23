#include "query/forall.hpp"
#include "query/environment.hpp"
#include "query/evaluate.hpp"
#include "query/quantifier_bind.hpp"

#include "query/logic.hpp"

namespace query {

Value ForAll::eval(std::shared_ptr<const Environment> env) const {
  auto gen = m_bind->iterate(env);
  while (true) {
    auto opt_b = gen->next();
    if (not opt_b.has_value()) {
      break;
    }
    auto result =
        evaluate<bool>(std::make_shared<Environment>(*env, *opt_b), *m_expr);
    if (!result.has_value()) {
      throw std::logic_error("Cannot evaluate expression to true/false.");
    }
    if (!result.value()) {
      return Value::of<bool>(false);
    }
  }
  return Value::of<bool>(true);
}

ForAll::ForAll(std::shared_ptr<const QuantifierBind> bind,
               std::shared_ptr<const IExpression> expr)
    : m_bind(std::move(bind)), m_expr(std::move(expr)) {}

} // namespace query
