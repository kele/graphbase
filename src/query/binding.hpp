#pragma once

#include <map>
#include <string>
#include <memory>

#include "query/expression.hpp"


namespace query {
using Binding = std::map<std::string, std::shared_ptr<const IExpression>>;

} // namespace query
