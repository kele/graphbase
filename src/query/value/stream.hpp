#pragma once

#include "patterns/istream.hpp"

#include <memory>

namespace query {
namespace value {

class Value;

class Stream : public patterns::IStream<std::unique_ptr<Value>> {
public:
  explicit Stream(
      std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>> stream);
  Stream(const Stream &s);
  Stream(Stream &&s);

  // TODO: get rid of this unique_ptr here
  std::optional<std::unique_ptr<Value>> next() final;
  std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>> clone() const;

private:
  std::unique_ptr<patterns::IStream<std::unique_ptr<Value>>> m_stream;
};

} // namespace value
} // namespace query
