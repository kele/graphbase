#pragma once

namespace patterns {

template<class T>
class IStream {
public:
  virtual ~IStream() {}

  virtual std::optional<T> next() = 0;
};

} // namespace patterns
