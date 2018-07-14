#include "query/list.hpp"

namespace query {

std::shared_ptr<const List>
List::build(std::vector<std::shared_ptr<const IExpression>> elements) {
  return std::make_shared<const List>(elements);
}

std::shared_ptr<const List> List::build(
    std::initializer_list<std::shared_ptr<const IExpression>> elements) {
  return build(std::vector<std::shared_ptr<const IExpression>>{elements});
}

} // namespace query
