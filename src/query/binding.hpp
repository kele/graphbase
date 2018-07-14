#pragma once

#include <map>
#include <memory>
#include <string>

#include "query/value.hpp"

namespace query {
using Binding = std::map<std::string, const Value>;

} // namespace query
