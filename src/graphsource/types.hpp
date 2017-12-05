#pragma once

#include <variant>

namespace graphbase {
namespace graphsource {

struct AllUndirected {
  size_t min_size;
  size_t max_size;
};

using Kind = std::variant<AllUndirected>;

}  // namespace graphsource
}  // namespace graphbase
