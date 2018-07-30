#pragma once

#include <map>
#include <memory>
#include <string>

#include "query/value/value.hpp"

namespace query {

using Binding = std::map<std::string, const value::Value>;

} // namespace query
