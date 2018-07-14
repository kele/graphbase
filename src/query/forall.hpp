#pragma once

#include "estd/estd.hpp"
#include "query/environment.hpp"
#include "query/iexpression.hpp"
#include "query/quantifier_bind.hpp"

namespace query {

class ForAll : public IExpression {
public:
  static std::shared_ptr<const ForAll>
  build(std::shared_ptr<const QuantifierBind> bind,
        std::shared_ptr<const IExpression> expr);

  Value eval(std::shared_ptr<const Environment> env) const final;

protected:
  ForAll(std::shared_ptr<const QuantifierBind> bind,
         std::shared_ptr<const IExpression> expr);

private:
  ForAll() = delete;

  std::shared_ptr<const QuantifierBind> m_bind;
  std::shared_ptr<const IExpression> m_expr;
};

} // namespace query
