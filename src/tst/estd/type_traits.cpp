#include "third_party/catch.hpp"

#include "estd/type_traits.hpp"

#include <tuple>

using namespace estd;

TEST_CASE("is_tuple", "[estd::is_tuple]") {
  static_assert(estd::is_tuple<std::tuple<bool, int>>::value);
  static_assert(not estd::is_tuple<std::pair<bool, int>>::value);
}
