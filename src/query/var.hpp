#pragma once

#include <memory>
#include <optional>

#include "query/expression.hpp"
#include "query/value.hpp"

namespace query {

class Var : public Expression<Var> {
public:
  static Var build(const Environment &env, std::string name);

private:
  explicit Var(std::string name);

  friend class Expression<Var>;
  Value evalImpl(const Environment &env) const;

  std::string m_name;
};

} // namespace query
