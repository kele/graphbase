#include "bins/oracle/client/client.hpp"

#include <iostream>

#include <grpc++/grpc++.h>

#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

using oracle::ListGraphsRequest;
using oracle::Oracle;

////////////////////////////////////////////////////////////////////////////////
// OracleClient implementation

OracleClient::OracleClient(std::shared_ptr<grpc::Channel> channel)
    : m_stub(Oracle::NewStub(channel)) {}

grpc::Status OracleClient::PrintGraphs(const ListGraphsRequest &request) {
  throw std::runtime_error("Not implemented.");

}
