#pragma once

#include "estd/estd.hpp"
#include "query/iexpression.hpp"
#include "query/value.hpp"

#include <memory>
#include <optional>

namespace query {

class Var : public IExpression, public estd::shared<Var> {
public:
  explicit Var(std::string name);

  Value eval(std::shared_ptr<const Environment> env) const final;

protected:
private:
  std::string m_name;
};

} // namespace query
