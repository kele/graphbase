#include "query/forall.hpp"
#include "query/evaluate.hpp"

namespace query {
estd::result<ForAll> ForAll::build(Bind bind, Expression expr) {
  return std::runtime_error("Not implemented.");
}

Value ForAll::eval(const Environment &env) const {
  auto gen = m_bind.iterate();
  while (true) {
    auto opt_b = gen.next();
    if (not opt_b.has_value()) {
      break;
    }
    if (evaluate<bool>(Environment::extend(env, *opt_b), m_expr)) {
      return Value::from<bool>(true);
    }
  }
  return Value::from<bool>(false);
}

ForAll::ForAll(Bind bind, Expression expr) : m_bind(bind), m_expr(expr) {}

} // namespace query
