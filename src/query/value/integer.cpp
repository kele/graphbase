#include "query/value/integer.hpp"

namespace query {
namespace value {

Integer::Integer(int v) : value(v) {}
Integer::operator int() const { return value; }

} // namespace value
} // namespace query
