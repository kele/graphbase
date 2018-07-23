#pragma once

#include "estd/estd.hpp"
#include "query/iexpression.hpp"
#include "query/value.hpp"

#include <memory>
#include <optional>

namespace query {

class True : public IExpression, public estd::shared<True> {
public:
  Value eval(std::shared_ptr<const Environment> env) const final;
};

class False : public IExpression, public estd::shared<False> {
public:
  Value eval(std::shared_ptr<const Environment> env) const final;
};

class Not : public IExpression, public estd::shared<Not> {
public:
  explicit Not(std::shared_ptr<const IExpression> expr);

  Value eval(std::shared_ptr<const Environment> env) const final;

private:
  std::shared_ptr<const IExpression> m_expr;
};

} // namespace query