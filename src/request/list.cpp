#include "request/list.hpp"

#include "request/expression.hpp"

namespace graphbase {
namespace request {

std::shared_ptr<const query::List> list(const oracle::List &lpb) {
  std::vector<std::shared_ptr<const query::IExpression>> expressions(lpb.elements_size());
  for (const auto &e : lpb.elements()) {
    expressions.emplace_back(std::move(expression(e)));
  }
  return query::List::build(std::move(expressions));
}

} // namespace request
} // namespace graphbase
