#include "query/var.hpp"
#include "estd/estd.hpp"
#include "query/environment.hpp"

namespace query {

Var::Var(std::string name) : m_name(std::move(name)) {}

value::Value Var::eval(std::shared_ptr<const Environment> env) const {
  return env->get(m_name);
}

} // namespace query
