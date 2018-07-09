#include "query/bind.hpp"
#include "query/expression.hpp"
#include "query/value.hpp"

namespace query {

estd::result<Bind> Bind::build(std::vector<std::string> names,
                               Expression expr) {
  if (names.size() == 0) {
    throw std::logic_error("Binding needs to have at least one variable");
  } else if (names.size() == 1) {
    if (!expr.is_generator()) {
      throw std::logic_error("The domain expression is not a generator.");
    }
    return Bind(names, static_cast<estd::generator<Value>>(expr));
  } else {
    throw std::runtime_error("Not implemented.");
  }
}

estd::generator<const Binding> Bind::iterate() const {
  auto domain = m_domain;
  auto name = m_name;
  auto f = [domain, name]() mutable -> std::optional<const Binding> {
    auto opt_v = domain.next();
    if (not opt_v.has_value()) {
      return std::nullopt;
    }
    Binding b;
    b.emplace(name, *opt_v);
    return std::make_optional(b);
  };
  return estd::generator<const Binding>(std::move(f));
}

Bind::Bind(std::vector<std::string> names, estd::generator<Value> domain)
    : m_name(names[0]), m_domain(domain) {}

} // namespace query
