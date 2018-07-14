#pragma once

#include <memory>
#include <optional>

#include "query/iexpression.hpp"
#include "query/value.hpp"

namespace query {

class True : public IExpression {
public:
  static std::shared_ptr<True> build();

  Value eval(std::shared_ptr<const Environment> env) const final;

protected:
  True() = default;
};

class False : public IExpression {
public:
  static std::shared_ptr<False> build();

  Value eval(std::shared_ptr<const Environment> env) const final;

protected:
  False() = default;
};

class Not : public IExpression {
public:
  static std::shared_ptr<Not> build(std::shared_ptr<const IExpression> expr);

  Value eval(std::shared_ptr<const Environment> env) const final;

protected:
  explicit Not(std::shared_ptr<const IExpression> expr);

private:
  std::shared_ptr<const IExpression> m_expr;
};

} // namespace query
