#pragma once

#include <grpc++/grpc++.h>

#include "protos/sv_oracle.grpc.pb.h"

////////////////////////////////////////////////////////////////////////////////
// OracleClient is the Oracle gRPC client.
class OracleClient {
public:
  explicit OracleClient(std::shared_ptr<grpc::Channel> channel);

  // PrintGraphs prints the graphs got using the given request.
  grpc::Status PrintGraphs(std::ostream *os,
                           const oracle::ListGraphsRequest &request);

protected:
  std::unique_ptr<oracle::Oracle::Stub> m_stub;
};
