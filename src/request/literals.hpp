#pragma once

#include "query/literals/literals.hpp"
#include "protos/sv_oracle.pb.h"

#include <memory>

namespace graphbase {
namespace request {

std::shared_ptr<const query::literals::Integer> integer_literal(const oracle::IntegerLiteral &ipb);

} // namespace request
} // namespace graphbase
