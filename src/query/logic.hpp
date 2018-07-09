#pragma once

#include <memory>
#include <optional>

#include "query/expression.hpp"
#include "query/value.hpp"

namespace query {

// TODO: can we have boolean expressions here?
// I think we can.

class True : public Expression<True> {
public:
  static std::shared_ptr<True> build();

protected:
  True() = default;

private:
  friend class Expression<True>;
  Value evalImpl(const Environment &env) const;
};

class False : public Expression<False> {
public:
  static std::shared_ptr<False> build();

protected:
  False() = default;

private:
  friend class Expression<False>;
  Value evalImpl(const Environment &env) const;
};

class Not : public Expression<Not> {
public:
  static Not build(const Environment &env, std::unique_ptr<Expression> expr);

private:
  explicit Not(std::unique_ptr<Expression> expr);

  friend class Expression<Not>;
  Value evalImpl(const Environment &env) const;

  std::unique_ptr<Expression> m_expr;
};

// TODO: things below need to be implemented
class Or : public Expression<Or> {
public:
  static Or build(const Environment &env, std::unique_ptr<Expression> lhs,
                  std::unique_ptr<Expression> rhs);

protected:
  Value evalImpl(const Environment &env) const;

private:
  explicit Or(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);

  std::unique_ptr<Expression> m_lhs;
  std::unique_ptr<Expression> m_rhs;
};

class And : public Expression<And> {
protected:
  Value evalImpl(const Environment &env) const;
};

class Xor : public Expression<Xor> {
protected:
  Value evalImpl(const Environment &env) const;
};

class IfThen : public Expression<IfThen> {
protected:
  Value evalImpl(const Environment &env) const;
};

class Iff : public Expression<Iff> {
protected:
  Value evalImpl(const Environment &env) const;
};

} // namespace query
