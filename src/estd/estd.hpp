#pragma once

#include <functional>

namespace estd {

template<class T>
class ref {
public:
  explicit ref(T& ref) : m_ref(ref) {}
  operator T& (){ return m_ref; }
  T& operator*() {
    return m_ref;
  }
  T* operator->() {
    return &m_ref;
  }

private:
  T& m_ref;
};

template<class T>
class cref {
public:
  explicit cref(const T& ref) : m_ref(ref) {}
  operator const T&() const{ return m_ref; }

  const T& operator*() const {
    return m_ref;
  }

  const T* operator->() const {
    return &m_ref;
  }

private:
  const T& m_ref;
};

inline bool require(bool exp, const char *msg) {
  if (!exp) {
    throw std::logic_error(msg);
  }
  return true;
}

inline bool require(bool exp, const char *msg, const char *call_site) {
  if (!exp) {
    throw std::logic_error(std::string("call site: ") + call_site + " | " + msg);
  }
  return true;
}

// TODO: this should be moved out of estd
template<class V>
class Generator {
public:
  explicit Generator(std::function<std::optional<V>()> f) : m_f(std::move(f)) {}

  std::optional<V> Next() {
    return m_f();
  }

  static Generator<V> Empty() {
    return Generator([]() { return std::nullopt; });
  }

  static Generator<V> Singleton(V v) {
    auto f = [v = std::move(v), has = true] () mutable -> std::optional<V> {
      if (has) {
        has = false;
        return v;
      }
      return std::nullopt;
    };
    return Generator(std::move(f));
  }

private:
  std::function<std::optional<V>()> m_f;
};

} // namespace estd
