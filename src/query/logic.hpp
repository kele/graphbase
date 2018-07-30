#pragma once

#include "estd/estd.hpp"
#include "query/iexpression.hpp"
#include "query/value/value.hpp"

#include <memory>
#include <optional>

namespace query {

class True : public IExpression, public estd::shared<True> {
public:
  value::Value eval(std::shared_ptr<const Environment> env) const final;
};

class False : public IExpression, public estd::shared<False> {
public:
  value::Value eval(std::shared_ptr<const Environment> env) const final;
};

class Not : public IExpression, public estd::shared<Not> {
public:
  explicit Not(std::shared_ptr<const IExpression> expr);

  value::Value eval(std::shared_ptr<const Environment> env) const final;

private:
  std::shared_ptr<const IExpression> m_expr;
};

} // namespace query
