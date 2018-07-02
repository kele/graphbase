#pragma once

#include <memory>

#include <grpc++/grpc++.h>

#include "oracle/oracle.hpp"
#include "protos/sv_oracle.grpc.pb.h"

////////////////////////////////////////////////////////////////////////////////
// OracleServer is an implementation of the oracle::Oracle::Service.
class OracleServer : public oracle::Oracle::Service {
public:
  explicit OracleServer(std::unique_ptr<graphbase::Oracle> oracle);

  // TODO(kele): add comment
  grpc::Status ListGraphs(grpc::ServerContext *context,
                          const oracle::ListGraphsRequest *request,
                          oracle::ListGraphsResponse *response) override;

private:
  std::unique_ptr<graphbase::Oracle> m_oracle;
};
