#include <fstream>
#include <iostream>

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <grpc++/grpc++.h>

#include "protos/sv_oracle.grpc.pb.h"

#include "bins/oracle/client/client.hpp"

void GraphRequestFromFile(std::string filename,
                          protos::services::GraphsRequest *request);

int main(int argc, char *argv[]) {
  OracleClient client(grpc::CreateChannel("localhost:51000",
                                          grpc::InsecureChannelCredentials()));

  if (argc <= 1) {
    std::cerr << "Missing arguments. Each argument should be a request "
                 "protocol buffer."
              << std::endl;
    return -1;
  }

  std::cout << "Processing " << argc - 1 << " requests..." << std::endl;
  for (int i = 1; i < argc; i++) {
    protos::services::GraphsRequest request;
    GraphRequestFromFile(argv[i], &request);

    std::cout << "#############################################" << std::endl;
    std::cout << "# Response for request " << i << std::endl;
    auto status = client.PrintGraphs(request);
    if (!status.ok()) {
      std::cout << "Error: " << status.error_message() << " - "
                << status.error_details() << std::endl;
    }
    std::cout << "# End of response for request " << i << std::endl
              << std::endl;
  }
}

void GraphRequestFromFile(std::string filename,
                          protos::services::GraphsRequest *request) {
  std::ifstream f(filename);
  google::protobuf::io::IstreamInputStream is(&f);
  auto parser = google::protobuf::TextFormat::Parser();
  bool status = parser.Parse(&is, request);
  if (!status) {
    throw std::runtime_error("Error parsing file: " + filename +
                             ". See stderr for details.");
  }
}
