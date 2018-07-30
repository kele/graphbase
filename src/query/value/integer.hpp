
#pragma once

namespace query {
namespace value {

struct Integer {
  Integer(int v);
  operator int() const;

  int value;
};

} // namespace value
} // namespace query
