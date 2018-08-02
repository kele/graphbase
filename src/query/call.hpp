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
  explicit Call(const std::vector<std::shared_ptr<const IExpression>> &args)
      : m_args(args) {
        if (std::tuple_size<typename F::Args>::value != args.size()) {
          throw std::range_error("NOT IMPLEMENTED YET");
          // TODO: std::string("Call to ") + F::name + " failed. Argument number mismatch.");
        }
  }

  value::Value eval(std::shared_ptr<const Environment> env) const final {
    auto t = evaluate<typename F::Args>(env, m_args);
    return evalImpl(env, std::move(t), std::make_index_sequence<std::tuple_size<typename F::Args>::value>());
  }

private:
  F m_f;
  std::vector<std::shared_ptr<const IExpression>> m_args;

  template<size_t... Is>
  value::Value evalImpl(std::shared_ptr<const Environment> env, typename F::Args argsTuple, std::index_sequence<Is...>) const {
    return m_f.call(std::get<Is>(argsTuple)...);
  }
};

} // namespace query
