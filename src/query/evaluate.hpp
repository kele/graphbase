#pragma once

#include "estd/type_traits.hpp"
#include "query/conversions/conversions.hpp"
#include "query/environment.hpp"
#include "query/iexpression.hpp"

#include <map>
#include <stdexcept>
#include <typeinfo>

namespace query {

template <class T>
std::optional<T> evaluate(std::shared_ptr<const Environment> env,
                          const IExpression &expr);
} // namespace query

namespace {

using namespace query;

template <size_t Index, class ArgsTuple>
auto eval_wrapper(const std::vector<std::shared_ptr<const IExpression>> &exprs,
                  std::shared_ptr<const Environment> env) {
  return *evaluate<typename std::tuple_element<Index, ArgsTuple>::type>(
      env, *exprs[Index]);
}

template <class Args, size_t... Is>
auto create_tuple(std::shared_ptr<const Environment> env,
                  const std::vector<std::shared_ptr<const IExpression>> &exprs,
                  std::index_sequence<Is...>) {
  return std::make_tuple(eval_wrapper<Is, Args>(exprs, env)...);
}
} // anonymous namespace

namespace query {

// TODO: get rid of the optional return value
template <class T>
std::optional<T> evaluate(std::shared_ptr<const Environment> env,
                          const IExpression &expr) {
  return conversions::to<T>(expr.eval(env));
}

template <class Args>
auto evaluate(std::shared_ptr<const Environment> env,
              const std::vector<std::shared_ptr<const IExpression>> &exprs) {
  static_assert(estd::is_tuple<Args>::value, "Args has to be a tuple.");
  return create_tuple<Args>(
      env, exprs, std::make_index_sequence<std::tuple_size<Args>::value>());
}

} // namespace query
