#include "graphsource/all_graphs.hpp"

#include <memory>

///////////////////////////////////////////////////////////////////////////////
// IncrementableBigNum implementation
IncrementableBigNum::IncrementableBigNum(size_t n) : m_mask(n, false) {}

bool IncrementableBigNum::inc() {
  auto it = std::begin(m_mask);
  while (it != std::end(m_mask)) {
    if (*it == false) {
      *it = true;
      return true;
    }
    *it = false;
    it++;
  }
  return false;
}

const std::vector<bool> &IncrementableBigNum::vec() const { return m_mask; }
