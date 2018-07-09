#include "query/quantifier_bind.hpp"
#include "estd/generator.hpp"
#include "query/conversions/conversions.hpp"
#include "query/expression.hpp"
#include "query/value.hpp"

namespace query {

std::shared_ptr<QuantifierBind>
QuantifierBind::build(std::vector<std::string> names,
                      std::shared_ptr<const List> expr) {
  if (names.size() == 0) {
    throw std::logic_error("Binding needs to have at least one variable");
  } else if (names.size() == 1) {
    auto f = [expr]() -> std::optional<std::shared_ptr<const IExpression>> {
      static auto it = expr->values().begin();

      if (it == expr->values().end()) {
        return std::nullopt;
      }

      auto v = std::make_optional(*it);
      it++;
      return v;
    };
    return std::make_shared<estd::enable_make_shared<QuantifierBind>>(
        std::move(names), estd::generator<std::shared_ptr<const IExpression>>(f));
  } else {
    throw std::runtime_error("QuantifierBind::build(): Not implemented.");
  }
}

std::shared_ptr<QuantifierBind>
QuantifierBind::build(std::string name, std::shared_ptr<const List> expr) {
  return build(std::vector<std::string>{name}, expr);
}

estd::generator<const Binding> QuantifierBind::iterate() const {
  auto domain = m_domain;
  auto name = m_name;
  auto f = [domain, name]() mutable -> std::optional<const Binding> {
    auto opt_v = domain.next();
    if (not opt_v.has_value()) {
      return std::nullopt;
    }
    Binding b;
    b.emplace(name, opt_v.value());
    return std::make_optional(b);
  };
  return estd::generator<const Binding>(std::move(f));
}

QuantifierBind::QuantifierBind(std::vector<std::string> names,
                               estd::generator<std::shared_ptr<const IExpression>> domain)
    : m_name(names[0]), m_domain(domain) {}

} // namespace query
