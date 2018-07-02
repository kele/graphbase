#pragma once

#include "estd/estd.hpp"
#include "query/bind.hpp"
#include "query/environment.hpp"
#include "query/expression.hpp"

namespace query {

class ForAll {
public:
  static estd::result<ForAll> build(Bind bind, Expression expr);

  Value eval(const Environment &env) const;

private:
  ForAll() = delete;
  ForAll(Bind bind, Expression expr);

  Bind m_bind;
  Expression m_expr;
};

} // namespace query
