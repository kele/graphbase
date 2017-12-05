#include <iostream>
#include <string>
#include <fstream>


#include <grpc++/grpc++.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>


#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

using namespace ::grpc;
using protos::Graph;
using protos::services::Count;
using protos::services::GraphsRequest;
using protos::services::Oracle;

class OracleClient {
 public:
  OracleClient(std::shared_ptr<grpc::Channel> channel)
      : m_stub(Oracle::NewStub(channel)) {}

  void PrintGraphs(const GraphsRequest &request) {
    Count response;
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

    auto status = reader->Finish();
    if (not status.ok()) {
      std::cerr << "Reader error: " << status.error_message() << std::endl;
      std::exit(-1);
    }
  }

 protected:
  std::unique_ptr<Oracle::Stub> m_stub;
};

int main(int argc, char *argv[]) {
  OracleClient client(grpc::CreateChannel("localhost:51000",
                                          grpc::InsecureChannelCredentials()));
  

  for (int i = 1; i < argc; i++) {
    std::ifstream f(argv[i]);
    google::protobuf::io::IstreamInputStream is(&f);

    auto parser = google::protobuf::TextFormat::Parser();

    GraphsRequest request;
    parser.Parse(&is, &request);

    std::cout << "#############################################" << std::endl;
    std::cout << "# Response for request " << i << std::endl;
    client.PrintGraphs(request);
    std::cout << "# End of response for request " << i << std::endl << std::endl;
  }
}
