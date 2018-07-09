#pragma once

#include "estd/estd.hpp"
#include "query/binding.hpp"
#include "query/expression.hpp"
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
  build(std::vector<std::string> names, std::shared_ptr<const List> expr);

  static std::shared_ptr<QuantifierBind>
  build(std::string name, std::shared_ptr<const List> expr);

  estd::generator<const Binding> iterate() const;

protected:
  QuantifierBind(std::vector<std::string> names, estd::generator<std::shared_ptr<const IExpression>> domain);

private:
  QuantifierBind() = delete;

  std::string m_name;
  estd::generator<std::shared_ptr<const IExpression>> m_domain;
};

} // namespace query
