#pragma once

#include "query/value.hpp"

#include <functional>
#include <map>
#include <optional>

namespace query {

class Environment {
public:
  Environment() = default;

  explicit Environment(const std::map<std::string, const Value> &b);
  explicit Environment(std::map<std::string, const Value> &&b);
  Environment(const Environment &base, const std::map<std::string, const Value> &b);

  std::optional<std::reference_wrapper<const Value>>
  get(const std::string &name) const;

  void add(const std::string &name, Value value);

private:
  std::map<std::string, const Value> m_binding;
};

} // namespace query
