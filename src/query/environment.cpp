#include "query/environment.hpp"
#include "query/binding.hpp"

namespace query {

Environment Environment::extend(const Environment &env, const Binding &b) {
  throw std::runtime_error("Not implemented.");
}

} // namespace query
