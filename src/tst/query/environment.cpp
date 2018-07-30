#include "third_party/catch.hpp"

#include "query/environment.hpp"

using namespace query;

TEST_CASE("Simple environment", "[environment]") {
  Environment env(std::map<std::string, const Value>{
      {"a", Value::of<Integer>(10)},
      {"b", Value::of<Integer>(7)},
      {"c", Value::of<Integer>(12345678)}
  });;

  auto a = env.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<Integer>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto b = env.get("b");
  REQUIRE(b.has_value());
  auto b_v = b.value().get().get<Integer>();
  REQUIRE(b_v.has_value());
  REQUIRE(*b_v == 7);

  auto c = env.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<Integer>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == 12345678);
}

TEST_CASE("Add variable to environment", "[environment]") {
  Environment env(std::map<std::string, const Value>{
      {"a", Value::of<Integer>(10)},
      {"c", Value::of<Integer>(12345678)}
  });;

  env.add("b", Value::of<Integer>(7));

  auto a = env.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<Integer>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto b = env.get("b");
  REQUIRE(b.has_value());
  auto b_v = b.value().get().get<Integer>();
  REQUIRE(b_v.has_value());
  REQUIRE(*b_v == 7);

  auto c = env.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<Integer>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == 12345678);
}

TEST_CASE("Add shadowing variable to environment", "[environment]") {
  Environment env(std::map<std::string, const Value>{
      {"a", Value::of<Integer>(10)},
      {"c", Value::of<Integer>(12345678)}
  });;

  env.add("c", Value::of<Integer>(9876));

  auto a = env.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<Integer>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto c = env.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<Integer>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == 9876);
}

TEST_CASE("Simple environment extension", "[environment]") {
  Environment env(std::map<std::string, const Value>{
      {"a", Value::of<Integer>(10)},
      {"c", Value::of<Integer>(12345678)}
  });;

  Environment extended(env, std::map<std::string, const Value>{{"b", Value::of<Integer>(7)}});

  auto a = extended.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<Integer>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto b = extended.get("b");
  REQUIRE(b.has_value());
  auto b_v = b.value().get().get<Integer>();
  REQUIRE(b_v.has_value());
  REQUIRE(*b_v == 7);

  auto c = extended.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<Integer>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == 12345678);
}

TEST_CASE("Shadowing environment extension", "[environment]") {
  Environment env(std::map<std::string, const Value>{
      {"a", Value::of<Integer>(10)},
      {"c", Value::of<Integer>(12345678)}
  });;

  Environment extended(env, std::map<std::string, const Value>{{"c", Value::of<Integer>(9876)}});

  auto a = extended.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<Integer>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto c = extended.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<Integer>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == 9876);
}
