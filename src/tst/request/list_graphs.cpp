#include "third_party/catch.hpp"

#include "request/list_graphs.hpp"
#include "protos/sv_oracle.pb.h"

using namespace graphbase;
using namespace request;


TEST_CASE("Forall", "[request::Forall]") {
  std::string proto_string = R"(
    expr: {
      forall: {
        var_name: "x"
        bind: {
          list: {
            elements: {
              expr: {
                bool_literal: {
                  boolean: true
                }
              }
            }
            elements: {
              expr: {
                bool_literal: {
                  boolean: true
                }
              }
            }
          }
        }
        expr: {
        }
      }
    }
  )";
  oracle::Expression expr_pb;

}
