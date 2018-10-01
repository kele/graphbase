#include "request/forall.hpp"
#include "request/expression.hpp"

namespace graphbase {
namespace request {
std::shared_ptr<const query::ForAll> for_all(const oracle::ForAll &fapb) {
  auto bind_expr = expression(fapb.bind());
  auto qb = query::QuantifierBind::build(fapb.var_name(), bind_expr);
  auto expr = expression(fapb.expr());
  return query::ForAll::build(qb, expr);
}

} // namespace request
} // namespace graphbase
