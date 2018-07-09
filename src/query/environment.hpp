#pragma once

#include "query/binding.hpp"

#include <deque>
#include <functional>
#include <optional>

namespace query {

class Environment {
public:
  explicit Environment(const Binding &b);
  explicit Environment(Binding &&b);

  static Environment extend(const Environment &env, const Binding &b);

  std::optional<std::reference_wrapper<const Value>>
  get(const std::string &name) const;

  void add(const std::string &name, Value value);

private:
  Binding m_binding;
};

} // namespace query
