#pragma once

#include "patterns/istream.hpp"
#include "query/value/value.hpp"

#include <memory>

namespace query {
namespace value {
namespace builtin {

class IntegerRange : public patterns::IStream<std::unique_ptr<Value>> {
public:
  IntegerRange(const IntegerRange &) = default;
  IntegerRange(IntegerRange &&) = default;

  IntegerRange(int begin, int end);
  IntegerRange(int begin, int end, int step);

  std::optional<std::unique_ptr<Value>> next() final;
  std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>> clone() const;

  operator Stream() const;

private:
  int m_begin, m_end, m_step;
};

} // namespace builtin
} // namespace value
} // namespace query
