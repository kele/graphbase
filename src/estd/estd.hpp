#pragma once

#include <functional>

namespace estd {

// require should be used as assert() from assert.h. The difference here being
// it throws a logic_error exception instead of aborting the program.
inline void require(bool cond, const char *msg) {
  if (!cond) {
    throw std::logic_error(msg);
  }
}

// require should be used as assert() from assert.h. The difference here being
// it throws a logic_error exception instead of aborting the program.
inline void require(bool cond, const char *msg, const char *call_site) {
  if (!cond) {
    throw std::logic_error(std::string("call site: ") + call_site + " | " +
                           msg);
  }
}

}  // namespace estd
