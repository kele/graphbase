#include "query/var.hpp"
#include "query/environment.hpp"

namespace query {

Var Var::build(const Environment &env, std::string name) {
  // TODO: check if var is in env
  return Var(std::move(name));
}

Value Var::evalImpl(const Environment &env) const {
  return env.get(m_name).value();
}

Var::Var(std::string name) : m_name(std::move(name)) {}

} // namespace query
