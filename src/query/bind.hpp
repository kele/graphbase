#pragma once

#include "estd/estd.hpp"
#include "query/binding.hpp"
#include "query/expression.hpp"
#include "query/value.hpp"

#include <optional>
#include <string>
#include <vector>

namespace query {
class Bind {
public:
  static estd::result<Bind> build(std::vector<std::string> names,
                                  Expression expr);

  estd::generator<const Binding> iterate() const;

private:
  Bind() = delete;
  Bind(std::vector<std::string> names, estd::generator<Value> domain);

  std::string m_name;
  estd::generator<Value> m_domain;
};

} // namespace query
