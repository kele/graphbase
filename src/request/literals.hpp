#pragma once

#include "protos/sv_oracle.pb.h"
#include "query/literals/literals.hpp"

#include <memory>

namespace graphbase {
namespace request {

std::shared_ptr<const query::literals::Integer>
integer_literal(const oracle::IntegerLiteral &);

std::shared_ptr<const query::literals::Boolean>
boolean_literal(const oracle::BooleanLiteral &);

} // namespace request
} // namespace graphbase
