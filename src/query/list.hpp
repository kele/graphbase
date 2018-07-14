#pragma once

#include <memory>
#include <vector>

namespace query {

class Environment;
class IExpression;

class List {
public:
  static std::shared_ptr<const List>
  build(std::vector<std::shared_ptr<const IExpression>> elements);

  static std::shared_ptr<const List>
  build(std::initializer_list<std::shared_ptr<const IExpression>> elements);

  const std::vector<std::shared_ptr<const IExpression>> &values() const {
    return m_elements;
  }

  List(std::vector<std::shared_ptr<const IExpression>> elements)
      : m_elements(elements) {}

private:
  std::vector<std::shared_ptr<const IExpression>> m_elements;
};

} // namespace query
