#include "query/value/stream.hpp"
#include "query/value/value.hpp"

namespace query {
namespace value {

Stream::Stream(
    std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>> stream)
    : m_stream(std::move(stream)) {}

Stream::Stream(const Stream &s) : m_stream(s.m_stream->clone()) {}

Stream::Stream(Stream &&s) : m_stream(std::move(s.m_stream)) {}

std::optional<std::unique_ptr<Value>> Stream::next() {
  return m_stream->next();
}

std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>>
Stream::clone() const {
  throw std::logic_error("Value::Stream::next() not implemented.");
}

} // namespace value
} // namespace query
