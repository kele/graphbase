#include <iostream>
#include <string>

#include <grpc++/grpc++.h>

#include "bins/oracle/server.hpp"
#include "graph/algo/bipartite.hpp"
#include "graphsource/all_graphs.hpp"
#include "oracle/oracle.hpp"
#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

using protos::services::Count;
using protos::services::GraphsRequest;

using namespace graphbase;

int main() {
  std::string server_address("0.0.0.0:51000");
  auto oracle = std::make_unique<Oracle>();
  oracle->RegisterSource(graphsource::Kind::All,
                         std::make_unique<undirected::OfSizeSource>(8));
  OracleServer oracle_server(std::move(oracle));

  grpc::ServerBuilder server_builder;
  server_builder.AddListeningPort(server_address,
                                  grpc::InsecureServerCredentials());
  server_builder.RegisterService(&oracle_server);

  try {
    auto server = server_builder.BuildAndStart();
    server->Wait();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Shutting down the server." << std::endl;
    std::exit(-1);
  }
}
