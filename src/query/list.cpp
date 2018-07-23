#include "query/list.hpp"

namespace query {

Value List::eval(std::shared_ptr<const Environment> env) const {
  std::vector<Value> vs;
  for (const auto &e : m_elements) {
    vs.push_back(e->eval(env));
  }
  return Value::of<std::vector<Value>>(vs);
}

} // namespace query
