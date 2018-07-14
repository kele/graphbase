#pragma once

#include <memory>
#include <optional>

#include "query/iexpression.hpp"
#include "query/value.hpp"

namespace query {

class Var : public IExpression {
public:
  static std::shared_ptr<Var> build(std::string name);

  Value eval(std::shared_ptr<const Environment> env) const final;

protected:
  explicit Var(std::string name);

private:
  std::string m_name;
};

} // namespace query
