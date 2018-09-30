#include "request/list_graphs.hpp"

#include "query/query.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::ForAll> for_all(const oracle::ForAll &fapb) {
  auto bind_expr = expression(fapb.bind());
  auto qb = query::QuantifierBind::build(fapb.var_name(), bind_expr);
  auto expr = expression(fapb.expr());
  return query::ForAll::build(qb, expr);
}

// TODO(kele): test ForAll
std::shared_ptr<const query::IExpression>
expression(const oracle::Expression &expr_pb) {
  switch (expr_pb.expr_case()) {
  case oracle::Expression::kForall:
    return for_all(expr_pb.forall());
  case oracle::Expression::kIntLiteral:
    // TODO(kele): implement
    return nullptr;
  case oracle::Expression::kBoolLiteral:
    // TODO(kele): implement
    return nullptr;
  case oracle::Expression::kList:
    // TODO(kele): implement
    return nullptr;
  default:
    // TODO(kele): signal that something is really really wrong
    return nullptr;
  }
}

} // namespace request
} // namespace graphbase
