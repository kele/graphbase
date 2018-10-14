#include "request/expression.hpp"

#include "request/forall.hpp"
#include "request/literals.hpp"
#include "request/list.hpp"

#include "query/query.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::IExpression>
expression(const oracle::Expression &expr_pb) {
  switch (expr_pb.expr_case()) {
  case oracle::Expression::kForall:
    return for_all(expr_pb.forall());
  case oracle::Expression::kIntLiteral:
    return integer_literal(expr_pb.int_literal());
  case oracle::Expression::kBoolLiteral:
    return boolean_literal(expr_pb.bool_literal());
  case oracle::Expression::kList:
    return list(expr_pb.list());
  default:
    // TODO(kele): signal that something is really really wrong
    return nullptr;
  }
}

} // namespace request
} // namespace graphbase
