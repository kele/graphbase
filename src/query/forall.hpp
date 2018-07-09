#pragma once

#include "estd/estd.hpp"
#include "query/environment.hpp"
#include "query/expression.hpp"
#include "query/quantifier_bind.hpp"

namespace query {

class ForAll : public Expression<ForAll> {
public:
  static std::shared_ptr<const ForAll>
  build(std::shared_ptr<const QuantifierBind> bind,
        std::shared_ptr<const IExpression> expr);

protected:
  ForAll(std::shared_ptr<const QuantifierBind> bind,
         std::shared_ptr<const IExpression> expr);

private:
  ForAll() = delete;

  friend class Expression<ForAll>;
  Value evalImpl(const Environment &env) const;

  std::shared_ptr<const QuantifierBind> m_bind;
  std::shared_ptr<const IExpression> m_expr;
};

} // namespace query
