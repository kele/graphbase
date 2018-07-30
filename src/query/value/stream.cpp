#include "query/value/stream.hpp"

namespace query {
namespace value {

std::optional<std::unique_ptr<Value>> Stream::next() {
  throw std::logic_error("Value::Stream::next() not implemented.");
}

std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>> Stream::clone() const {
  throw std::logic_error("Value::Stream::next() not implemented.");
}

} // namespace value
} // namespace query
