#pragma once

#include "estd/estd.hpp"
#include "patterns/istream.hpp"
#include "query/binding.hpp"
#include "query/iexpression.hpp"
#include "query/list.hpp"
#include "query/value/value.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace query {
class QuantifierBind : public estd::shared<QuantifierBind> {
public:
  QuantifierBind(std::string name, std::shared_ptr<const IExpression> domain);

  std::unique_ptr<patterns::IStream<const Binding>>
  iterate(std::shared_ptr<const Environment> env) const;

private:
  QuantifierBind() = delete;

  class BindingStream : public patterns::IStream<const Binding> {
  public:
    BindingStream(std::string name, std::vector<value::Value> values);
    std::optional<const Binding> next() final;

  private:
    int m_next = 0;
    const std::string m_name;
    const std::vector<value::Value> m_values;
  };

  std::string m_name;
  std::shared_ptr<const IExpression> m_domain;
};

} // namespace query
