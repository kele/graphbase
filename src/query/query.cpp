#include "query/query.hpp"

namespace query {

bool Expression::is_generator() const {
  throw std::runtime_error("Not implemented.");
}

Expression::operator estd::generator<Value>() const {
  throw std::runtime_error("Not implemented.");
}

} // namespace query
