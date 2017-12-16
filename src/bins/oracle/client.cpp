#include "bins/oracle/client.hpp"

#include <iostream>

#include <grpc++/grpc++.h>

#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

using namespace ::grpc;
using protos::Graph;
using protos::services::GraphsRequest;
using protos::services::Oracle;

////////////////////////////////////////////////////////////////////////////////
// OracleClient implementation

OracleClient::OracleClient(std::shared_ptr<grpc::Channel> channel)
    : m_stub(Oracle::NewStub(channel)) {}

grpc::Status OracleClient::PrintGraphs(const GraphsRequest &request) {
  // TODO(https://github.com/kele/graphbase/issues/1): set a deadline
  ClientContext ctx;
  auto reader = m_stub->GetGraphs(&ctx, request);

  Graph g;
  while (reader->Read(&g)) {
    if (g.has_directed()) {
      std::cout << g.directed().digraph6() << std::endl;
    } else if (g.has_undirected()) {
      std::cout << g.undirected().graph6() << std::endl;
    }
  }

  return reader->Finish();
}
