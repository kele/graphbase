#pragma once

#include "estd/estd.hpp"
#include "query/value/value.hpp"
#include "query/evaluate.hpp"
#include "query/iexpression.hpp"
#include "query/var.hpp"

#include <vector>
#include <memory>
#include <tuple>


namespace query {

template<size_t Index, class ArgsTuple>
auto eval_wrapper(
    const std::vector<std::shared_ptr<const IExpression>>& exprs,
    std::shared_ptr<const Environment> env) {
  return *evaluate<typename std::tuple_element<Index, ArgsTuple>::type>(env, *exprs[Index]);
}

template<class Args, size_t... Is>
auto create_tuple_impl(
    const std::vector<std::shared_ptr<const IExpression>>& exprs,
    std::shared_ptr<const Environment> env,
    std::index_sequence<Is...>) {
  return std::make_tuple(eval_wrapper<Is, Args>(exprs, env)...);
}


template<class Args, size_t N>
auto create_tuple(
    const std::vector<std::shared_ptr<const IExpression>>& exprs,
    std::shared_ptr<const Environment> env) {
  return create_tuple_impl<Args>(exprs, env, std::make_index_sequence<N>());
}

template<class F>
class Call : public IExpression, public estd::shared<Var> {
public:
  using Args = typename F::Args;

  explicit Call(const std::vector<std::shared_ptr<const IExpression>> &args) : m_args(args) {}

  value::Value eval(std::shared_ptr<const Environment> env) const final {
    auto t = create_tuple<Args, std::tuple_size<Args>::value>(m_args, env);
    return m_f.call(t);
  }

private:
  F m_f;
  std::vector<std::shared_ptr<const IExpression>> m_args;
};

} // namespace query
