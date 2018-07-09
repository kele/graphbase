#include "query/list.hpp"

namespace query {

std::shared_ptr<const List>
List::build(std::vector<std::shared_ptr<const IExpression>> elements) {
  return std::make_shared<const List>(elements);
}

} // namespace query
