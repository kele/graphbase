#include "bins/oracle/client/client.hpp"

#include <iostream>

#include <grpc++/grpc++.h>

#include "protos/sv_oracle.grpc.pb.h"

using oracle::ListGraphsRequest;
using oracle::ListGraphsResponse;
using oracle::Oracle;

////////////////////////////////////////////////////////////////////////////////
// OracleClient implementation

OracleClient::OracleClient(std::shared_ptr<grpc::Channel> channel)
    : m_stub(Oracle::NewStub(channel)) {}

grpc::Status OracleClient::PrintGraphs(std::ostream *os,
                                       const ListGraphsRequest &request) {
  grpc::ClientContext ctx;

  ListGraphsResponse resp;
  grpc::Status status = m_stub->ListGraphs(&ctx, request, &resp);
  if (not status.ok()) {
    return status;
  }

  // TODO(kele): actually process the graphs
  // TODO(kele): implement paging processing
  return status;
}
