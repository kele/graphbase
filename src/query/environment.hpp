#pragma once

#include "query/binding.hpp"

#include <deque>
#include <functional>
#include <optional>

namespace query {

class Environment {
public:
  Environment() = default;

  explicit Environment(const Binding &b);
  explicit Environment(Binding &&b);
  Environment(const Environment &base, const Binding &b);

  std::optional<std::reference_wrapper<const value::Value>>
  try_get(const std::string &name) const;

  const value::Value &get(const std::string &name) const;

  void add(const std::string &name, value::Value value);

private:
  std::map<std::string, const value::Value> m_binding;
};

} // namespace query
