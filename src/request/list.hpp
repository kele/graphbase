#pragma once

#include <memory>

#include "protos/sv_oracle.pb.h"
#include "query/list.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::List> list(const oracle::List &);

} // namespace request
} // namespace graphbase
