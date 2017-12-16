#pragma once

namespace estd {

// generator provides a (possibly infinite) stream of values
template <class V>
class generator {
 public:
  // generator receives a function used to create values. On each call of
  // generator::next(), the given function is being called.
  explicit generator(std::function<std::optional<V>()> f) : m_f(std::move(f)) {}

  // next returns a value if one is available, std::nullopt instead
  std::optional<V> next() { return m_f(); }

  // empty generator
  static generator<V> empty() {
    return generator([]() { return std::nullopt; });
  }

  // singleton is a generator that returns a single value
  static generator<V> singleton(V v) {
    auto f = [ v = std::move(v), has = true ]() mutable->std::optional<V> {
      if (has) {
        has = false;
        return v;
      }
      return std::nullopt;
    };
    return generator(std::move(f));
  }

 private:
  std::function<std::optional<V>()> m_f;
};

}  // namespace estd
