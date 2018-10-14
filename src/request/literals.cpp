#include "request/literals.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::literals::Integer>
integer_literal(const oracle::IntegerLiteral &ipb) {
  return query::literals::Integer::build(ipb.integer());
}

std::shared_ptr<const query::literals::Boolean>
boolean_literal(const oracle::BooleanLiteral &bpb) {
  return query::literals::Boolean::build(bpb.boolean());
}

} // namespace request
} // namespace graphbase
