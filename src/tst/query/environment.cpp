#include "third_party/catch.hpp"

#include "query/environment.hpp"

using namespace query;

TEST_CASE("Simple environment", "[environment]") {
  Environment env(Binding{
      {"a", Value::from<int>(10)},
      {"b", Value::from<int>(7)},
      {"c", Value::from<std::string>("blahblahblah")}
  });;

  auto a = env.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<int>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto b = env.get("b");
  REQUIRE(b.has_value());
  auto b_v = b.value().get().get<int>();
  REQUIRE(b_v.has_value());
  REQUIRE(*b_v == 7);

  auto c = env.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<std::string>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == "blahblahblah");
}

TEST_CASE("Add variable to environment", "[environment]") {
  Environment env(Binding{
      {"a", Value::from<int>(10)},
      {"c", Value::from<std::string>("blahblahblah")}
  });;

  env.add("b", Value::from<int>(7));

  auto a = env.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<int>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto b = env.get("b");
  REQUIRE(b.has_value());
  auto b_v = b.value().get().get<int>();
  REQUIRE(b_v.has_value());
  REQUIRE(*b_v == 7);

  auto c = env.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<std::string>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == "blahblahblah");
}

TEST_CASE("Add shadowing variable to environment", "[environment]") {
  Environment env(Binding{
      {"a", Value::from<int>(10)},
      {"c", Value::from<std::string>("blahblahblah")}
  });;

  env.add("c", Value::from<std::string>("shadowed"));

  auto a = env.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<int>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto c = env.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<std::string>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == "shadowed");
}

TEST_CASE("Simple environment extension", "[environment]") {
  Environment env(Binding{
      {"a", Value::from<int>(10)},
      {"c", Value::from<std::string>("blahblahblah")}
  });;

  Environment extended(env, Binding{{"b", Value::from<int>(7)}});

  auto a = extended.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<int>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto b = extended.get("b");
  REQUIRE(b.has_value());
  auto b_v = b.value().get().get<int>();
  REQUIRE(b_v.has_value());
  REQUIRE(*b_v == 7);

  auto c = extended.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<std::string>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == "blahblahblah");
}

TEST_CASE("Shadowing environment extension", "[environment]") {
  Environment env(Binding{
      {"a", Value::from<int>(10)},
      {"c", Value::from<std::string>("blahblahblah")}
  });;

  Environment extended(env, Binding{{"c", Value::from<std::string>("shadowed")}});

  auto a = extended.get("a");
  REQUIRE(a.has_value());
  auto a_v = a.value().get().get<int>();
  REQUIRE(a_v.has_value());
  REQUIRE(*a_v == 10);

  auto c = extended.get("c");
  REQUIRE(c.has_value());
  auto c_v = c.value().get().get<std::string>();
  REQUIRE(c_v.has_value());
  REQUIRE(*c_v == "shadowed");
}
