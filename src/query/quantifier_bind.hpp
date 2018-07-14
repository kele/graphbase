#pragma once

#include "estd/estd.hpp"
#include "estd/generator.hpp"
#include "query/binding.hpp"
#include "query/iexpression.hpp"
#include "query/list.hpp"
#include "query/value.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace query {
class QuantifierBind {
public:
  static std::shared_ptr<QuantifierBind>
  build(std::string name, std::shared_ptr<const List> expr);

  estd::generator<const Binding>
  iterate(std::shared_ptr<const Environment> env) const;

protected:
  QuantifierBind(std::string name,
                 estd::generator<std::shared_ptr<const IExpression>> domain);

private:
  QuantifierBind() = delete;

  std::string m_name;
  estd::generator<std::shared_ptr<const IExpression>> m_domain;
};

} // namespace query
