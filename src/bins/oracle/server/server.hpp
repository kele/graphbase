#pragma once

#include <grpc++/grpc++.h>

#include "oracle/oracle.hpp"
#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

////////////////////////////////////////////////////////////////////////////////
// OracleServer is an implementation of the protos::services::Oracle::Service.
class OracleServer : public protos::services::Oracle::Service {
public:
  explicit OracleServer(std::unique_ptr<graphbase::Oracle> oracle);

  // GetGraphs returns the graphs retrieved using GraphInputSpec that pass the
  // given predicate.
  grpc::Status GetGraphs(grpc::ServerContext *context,
                         const protos::services::GraphsRequest *request,
                         grpc::ServerWriter<protos::Graph> *writer) override;
  // GetCount returns the count of graphs retrieved using GraphInputSpec that
  // pass the given predicate.
  grpc::Status GetCount(grpc::ServerContext *context,
                        const protos::services::GraphsRequest *request,
                        protos::services::Count *response) override;

private:
  std::unique_ptr<graphbase::Oracle> m_oracle;
};
