#pragma once

#include <functional>
#include <variant>

namespace estd {

// require should be used as assert() from assert.h. The difference here being
// it throws a logic_error exception instead of aborting the program.
inline void require(bool cond, const char *msg) {
  if (!cond) {
    throw std::logic_error(msg);
  }
}

// require should be used as assert() from assert.h. The difference here being
// it throws a logic_error exception instead of aborting the program.
inline void require(bool cond, const char *msg, const char *call_site) {
  if (!cond) {
    throw std::logic_error(std::string("call site: ") + call_site + " | " +
                           msg);
  }
}

// either represents a type that can hold either L or R. It is basically a
// speciailization of std::variant.
template <class L, class R> struct either {
  either(const R &&r) : m_v(r) {}
  either(R &&r) : m_v(std::move(r)) {}

  either(const L &&l) : m_v(l) {}
  either(L &&l) : m_v(std::move(l)) {}

  template <class V> bool is() const { return std::holds_alternative<V>(m_v); }

  bool is_left() const { return is<L>(); }

  bool is_right() const { return is<R>(); }

  const L &left() const { return std::get<L>(m_v); }
  L &left() { return std::get<L>(m_v); }

  const R &right() const { return std::get<R>(m_v); }
  R &right() { return std::get<R>(m_v); }

private:
  std::variant<L, R> m_v;
};

// result is a thin wrapper for either with L = std::exception for holding
// optional errors.
template <class R> struct result : either<R, std::exception> {
  result(const R &&r) : either<R, std::exception>(r) {}
  result(R &&r) : either<R, std::exception>(std::move(r)) {}

  result(const std::exception &&e) : either<R, std::exception>(e) {}
  result(std::exception &&e) : either<R, std::exception>(std::move(e)) {}

  const R &value() const { return this->left(); }

  R &value() { return this->left(); }

  bool is_err() const { return this->is_right(); }
};

} // namespace estd
