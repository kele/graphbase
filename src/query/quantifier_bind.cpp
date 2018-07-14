#include "query/quantifier_bind.hpp"
#include "estd/generator.hpp"
#include "query/conversions/conversions.hpp"
#include "query/iexpression.hpp"
#include "query/value.hpp"

namespace query {

std::shared_ptr<QuantifierBind>
QuantifierBind::build(std::string name, std::shared_ptr<const List> expr) {
  auto f = [expr, it = expr->values().begin()]() mutable
      -> std::optional<std::shared_ptr<const IExpression>> {
    if (it == expr->values().end()) {
      return std::nullopt;
    }
    auto v = std::make_optional(*it);
    it++;
    return v;
  };
  return std::make_shared<estd::enable_make_shared<QuantifierBind>>(
      std::move(name), estd::generator<std::shared_ptr<const IExpression>>(f));
}

estd::generator<const Binding>
QuantifierBind::iterate(std::shared_ptr<const Environment> env) const {
  auto f = [domain = m_domain, name = m_name,
            env = env]() mutable -> std::optional<const Binding> {
    auto opt_v = domain.next();
    if (not opt_v.has_value()) {
      return std::nullopt;
    }
    Binding b;
    b.emplace(name, opt_v.value()->eval(env));
    return std::make_optional(b);
  };
  return estd::generator<const Binding>(std::move(f));
}

QuantifierBind::QuantifierBind(
    std::string name,
    estd::generator<std::shared_ptr<const IExpression>> domain)
    : m_name(name), m_domain(domain) {}

} // namespace query
