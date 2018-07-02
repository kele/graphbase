#include <iostream>
#include <string>

#include <grpc++/grpc++.h>

#include "bins/oracle/server/server.hpp"
#include "oracle/oracle.hpp"

using namespace graphbase;

int main() {
  grpc::ServerBuilder server_builder;
  server_builder.AddListeningPort("0.0.0.0:51000",
                                  grpc::InsecureServerCredentials());

  OracleServer oracle_server(std::make_unique<Oracle>());
  server_builder.RegisterService(&oracle_server);
  try {
    auto server = server_builder.BuildAndStart();
    server->Wait();
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Shutting down the server." << std::endl;
    std::exit(-1);
  }
}
