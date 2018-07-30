#pragma once

#include "estd/estd.hpp"
#include "query/iexpression.hpp"
#include "query/value/value.hpp"

#include <memory>
#include <vector>

namespace query {

class Environment;

class List : public IExpression, public estd::shared<List> {
public:
  const std::vector<std::shared_ptr<const IExpression>> &values() const {
    return m_elements;
  }

  value::Value eval(std::shared_ptr<const Environment> env) const final;

  explicit List(
      std::initializer_list<std::shared_ptr<const IExpression>> elements)
      : m_elements(elements) {}

  explicit List(std::vector<std::shared_ptr<const IExpression>> elements)
      : m_elements(elements) {}

private:
  std::vector<std::shared_ptr<const IExpression>> m_elements;
};

} // namespace query
