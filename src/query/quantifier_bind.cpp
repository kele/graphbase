#include "query/quantifier_bind.hpp"
#include "patterns/istream.hpp"
#include "query/conversions/conversions.hpp"
#include "query/evaluate.hpp"
#include "query/iexpression.hpp"

namespace query {

using value::Value;

QuantifierBind::QuantifierBind(std::string name,
                               std::shared_ptr<const IExpression> domain)
    : m_name(name), m_domain(domain) {}

std::unique_ptr<patterns::IStream<const Binding>>
QuantifierBind::iterate(std::shared_ptr<const Environment> env) const {
  // TODO: lazy evaluation
  auto list = evaluate<std::vector<Value>>(env, *m_domain);
  return std::make_unique<BindingStream>(m_name, std::move(*list));
}

QuantifierBind::BindingStream::BindingStream(std::string name,
                                             std::vector<Value> values)
    : m_name(name), m_values(std::move(values)) {}

std::unique_ptr<patterns::IStream<const Binding>>
QuantifierBind::BindingStream::clone() const {
  return std::make_unique<BindingStream>(*this);
}

std::optional<const Binding> QuantifierBind::BindingStream::next() {
  if (m_next >= m_values.size()) {
    return std::nullopt;
  }
  return Binding{{m_name, m_values[m_next++]}};
}

} // namespace query
