#include "request/literals.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::literals::Integer>
integer_literal(const oracle::IntegerLiteral &ipb) {
  return query::literals::Integer::build(ipb.integer());
}

} // namespace request
} // namespace graphbase
