#include "bins/oracle/server/server.hpp"

#include <memory>
#include <stdexcept>

#include <grpc++/grpc++.h>

#include "conversions/undirected.hpp"
#include "graph/algo/undirected_predicates.hpp"
#include "oracle/oracle.hpp"
#include "protos/sv_oracle.grpc.pb.h"

using namespace graphbase;
using namespace graphbase::graph::undirected;

////////////////////////////////////////////////////////////////////////////////
// OracleServer implementation

OracleServer::OracleServer(std::unique_ptr<graphbase::Oracle> oracle)
    : m_oracle(std::move(oracle)) {}

grpc::Status
OracleServer::ListGraphs(grpc::ServerContext *context,
                         const oracle::ListGraphsRequest *request,
                         oracle::ListGraphsResponse *response) try {


  auto graphs = m_oracle->GetUndirectedGraphs(Kind::All, std::make_shared<predicates::IsBipartite>());

  return grpc::Status();

} catch (const std::exception &e) {
  return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
}
