#pragma once

#include "protos/sv_oracle.pb.h"
#include "query/iexpression.hpp"

#include <memory>

namespace graphbase {
namespace request {

std::shared_ptr<const query::IExpression>
expression(const oracle::Expression &expr_pb);

} // namespace request
} // namespace graphbase
