#pragma once

#include "estd/estd.hpp"
#include "estd/type_traits.hpp"
#include "query/evaluate.hpp"
#include "query/iexpression.hpp"
#include "query/value/value.hpp"
#include "query/var.hpp"

#include <memory>
#include <tuple>
#include <vector>

namespace query {

template <class F> class Call : public IExpression, public estd::shared<Var> {
public:
  static_assert(estd::is_tuple<typename F::Args>::value, "Call::Args has to be a tuple.");

  using Args = typename F::Args;

  explicit Call(const std::vector<std::shared_ptr<const IExpression>> &args)
      : m_args(args) {}

  value::Value eval(std::shared_ptr<const Environment> env) const final {
    auto t = evaluate<Args, std::tuple_size<Args>::value>(env, m_args);
    return m_f.call(t);
  }

private:
  F m_f;
  std::vector<std::shared_ptr<const IExpression>> m_args;
};

} // namespace query
