#include "query/value/builtin/range.hpp"

namespace query {
namespace value {
namespace builtin {

IntegerRange::IntegerRange(int begin, int end)
    : m_begin(begin), m_end(end), m_step(1) {}
IntegerRange::IntegerRange(int begin, int end, int step)
    : m_begin(begin), m_end(end), m_step(step) {}

std::optional<std::unique_ptr<Value>> IntegerRange::next() {
  if (m_step > 0 && m_begin >= m_end) {
    // Up
    return std::nullopt;
  } else if (m_step < 0 && m_begin <= m_end) {
    // Down
    return std::nullopt;
  }
  int r = m_begin;
  m_begin += m_step;
  return std::make_unique<Value>(Value::of(Integer(r)));
}

IntegerRange::operator Stream() const { return Stream(clone()); }

std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>>
IntegerRange::clone() const {
  return std::make_unique<IntegerRange>(*this);
}

} // namespace builtin
} // namespace value
} // namespace query
