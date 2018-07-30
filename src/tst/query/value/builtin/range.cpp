#include "third_party/catch.hpp"

#include "query/value/builtin/range.hpp"
#include "query/value/stream.hpp"

using query::value::Integer;
using query::value::Stream;
using query::value::Value;
using query::value::builtin::IntegerRange;

TEST_CASE("IntegerRange(2, 7) = {2, 3, 4, 5, 6}", "[query::value::builtin::range]") {
  IntegerRange ir(2, 7);

  const std::vector<int> expected{2, 3, 4, 5, 6};
  std::vector<int> got;

  Stream s = ir;
  std::optional<std::unique_ptr<Value>> op;
  while((op = s.next()).has_value()) {
    got.push_back(op.value()->get<Integer>().value);
  }
  REQUIRE(expected == got);
}

TEST_CASE("IntegerRange(2, 15, 3) = {2, 5, 8, 11, 14}", "[query::value::builtin::range]") {
  IntegerRange ir(2, 15, 3);

  const std::vector<int> expected{2, 5, 8, 11, 14};
  std::vector<int> got;

  Stream s = ir;
  std::optional<std::unique_ptr<Value>> op;
  while((op = s.next()).has_value()) {
    got.push_back(op.value()->get<Integer>().value);
  }
  REQUIRE(expected == got);
}

TEST_CASE("IntegerRange(2, 2) = {}", "[query::value::builtin::range]") {
  IntegerRange ir(2, 2);

  const std::vector<int> expected{};
  std::vector<int> got;

  Stream s = ir;
  std::optional<std::unique_ptr<Value>> op;
  while((op = s.next()).has_value()) {
    got.push_back(op.value()->get<Integer>().value);
  }
  REQUIRE(expected == got);
}

TEST_CASE("IntegerRange(2, 0) = {}", "[query::value::builtin::range]") {
  IntegerRange ir(2, 0);

  const std::vector<int> expected{};
  std::vector<int> got;

  Stream s = ir;
  std::optional<std::unique_ptr<Value>> op;
  while((op = s.next()).has_value()) {
    got.push_back(op.value()->get<Integer>().value);
  }
  REQUIRE(expected == got);
}

TEST_CASE("IntegerRange(2, 0, -1) = {2, 1}", "[query::value::builtin::range]") {
  IntegerRange ir(2, 0, -1);

  const std::vector<int> expected{2, 1};
  std::vector<int> got;

  Stream s = ir;
  std::optional<std::unique_ptr<Value>> op;
  while((op = s.next()).has_value()) {
    got.push_back(op.value()->get<Integer>().value);
  }
  REQUIRE(expected == got);
}
