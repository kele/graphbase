#include <fstream>
#include <iostream>

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <grpc++/grpc++.h>

#include "protos/sv_oracle.grpc.pb.h"

#include "bins/oracle/client.hpp"

void GraphRequestFromFile(std::string filename,
                          protos::services::GraphsRequest *request);

int main(int argc, char *argv[]) {
  OracleClient client(grpc::CreateChannel("localhost:51000",
                                          grpc::InsecureChannelCredentials()));

  for (int i = 1; i < argc; i++) {
    protos::services::GraphsRequest request;
    GraphRequestFromFile(argv[i], &request);

    std::cout << "#############################################" << std::endl;
    std::cout << "# Response for request " << i << std::endl;
    client.PrintGraphs(request);
    std::cout << "# End of response for request " << i << std::endl
              << std::endl;
  }
}

void GraphRequestFromFile(std::string filename,
                          protos::services::GraphsRequest *request) {
  std::ifstream f(filename);
  google::protobuf::io::IstreamInputStream is(&f);

  auto parser = google::protobuf::TextFormat::Parser();

  parser.Parse(&is, request);
}