#pragma once

#include <optional>
#include <memory>

namespace patterns {

template<class T>
class IStream {
public:
  virtual ~IStream() {}

  virtual std::unique_ptr<IStream<T>> clone() const = 0;

  virtual std::optional<T> next() = 0;
};

} // namespace patterns
