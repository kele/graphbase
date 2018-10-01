#include "request/expression.hpp"
#include "request/forall.hpp"

#include "query/query.hpp"

namespace graphbase {
namespace request {

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
