#include "query/value.hpp"

namespace query {

Integer::Integer(int v) : value(v) {}
Integer::operator int() const { return value; }

std::optional<std::unique_ptr<Value>> Stream::next() {
  throw std::logic_error("Value::Stream::next() not implemented.");
}

} // namespace query
