#pragma once

#include <type_traits>

namespace estd {

template <class T, class... Args> class is_tuple : public std::false_type {};

template <class... Args>
class is_tuple<std::tuple<Args...>> : public std::true_type {};

} // namespace estd
