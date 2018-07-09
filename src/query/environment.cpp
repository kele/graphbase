#include "query/environment.hpp"
#include "query/binding.hpp"

namespace query {

Environment::Environment(const Binding &b) : m_binding{b} {}

Environment::Environment(Binding &&b) : m_binding{std::move(b)} {}

Environment Environment::extend(const Environment &env, const Binding &b) {
  Environment new_env(env);
  for (const auto &kv : b) {
    new_env.add(kv.first, kv.second);
  }
  return new_env;
}

std::optional<std::reference_wrapper<const Value>>
Environment::get(const std::string &name) const {
  auto it = m_binding.find(name);
  if (it != m_binding.end()) {
    return it->second;
  }
  return std::nullopt;
}

void Environment::add(const std::string &name, Value value) {
  m_binding.erase(name);
  m_binding.emplace(name, std::move(value));
}

} // namespace query
