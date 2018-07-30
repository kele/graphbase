#pragma once

#include "patterns/istream.hpp"

#include <memory>

namespace query {
namespace value {

class Value;

class Stream : public patterns::IStream<std::unique_ptr<Value>> {
public:
  std::optional<std::unique_ptr<Value>> next() final;
};

} // namespace value
} // namespace query
