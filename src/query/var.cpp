#include "query/var.hpp"
#include "estd/estd.hpp"
#include "query/environment.hpp"

namespace query {

std::shared_ptr<Var> Var::build(std::string name) {
  return std::make_shared<estd::enable_make_shared<Var>>(std::move(name));
}

Value Var::eval(std::shared_ptr<const Environment> env) const {
  return env->get(m_name).value();
}

Var::Var(std::string name) : m_name(std::move(name)) {}

} // namespace query
