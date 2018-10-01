#pragma once

#include <memory>

#include "protos/sv_oracle.pb.h"
#include "query/forall.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::ForAll> for_all(const oracle::ForAll &fapb);

} // namespace request
} // namespace graphbase
