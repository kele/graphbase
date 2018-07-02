#include "bins/oracle/server/server.hpp"

#include <memory>
#include <stdexcept>

#include <grpc++/grpc++.h>

#include "conversions/undirected.hpp"
#include "graph/algo/undirected_predicates.hpp"
#include "oracle/oracle.hpp"
#include "protos/sv_oracle.grpc.pb.h"

using namespace grpc;
using namespace graphbase;

////////////////////////////////////////////////////////////////////////////////
// OracleServer implementation

OracleServer::OracleServer(std::unique_ptr<graphbase::Oracle> oracle)
    : m_oracle(std::move(oracle)) {}

grpc::Status
OracleServer::ListGraphs(grpc::ServerContext *context,
                         const oracle::ListGraphsRequest *request,
                         oracle::ListGraphsResponse *response) try {
  throw std::runtime_error("Not implemented.");
} catch (const std::exception &e) {
  return Status(StatusCode::INTERNAL, e.what());
}
