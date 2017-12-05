#include "bins/oracle/server.hpp"

#include <iostream>
#include <string>

#include <grpc++/grpc++.h>

#include "conversions/undirected.hpp"
#include "graph/algo/undirected_predicates.hpp"
#include "oracle/oracle.hpp"
#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

// TODO: clean this up
using protos::services::Count;
using protos::services::GraphsRequest;

using namespace graphbase;
using namespace grpc;
using namespace protos;

using graph::edge_t;
using graph::undirected::BasicGraph;

OracleServer::OracleServer(std::unique_ptr<Oracle> oracle)
    : m_oracle(std::move(oracle)) {}

Status OracleServer::GetGraphs(ServerContext* context,
                               const GraphsRequest* request,
                               ServerWriter<Graph>* writer) {

  auto gen = m_oracle->GetUndirectedGraphs(
      Kind::All, std::make_shared<graph::undirected::algo::IsBipartite>());
  std::optional<std::shared_ptr<const BasicGraph>> opt_g;

  size_t limit = request->limit();

  size_t count = 0;
  while ((opt_g = gen.Next())) {
    const BasicGraph& g = *opt_g.value();
    Graph response;
    response.mutable_undirected()->set_graph6(
        graphbase::conversions::ToGraph6(g));
    writer->Write(response);

    count++;

    if (limit > 0 && count >= limit) {
      // Ok, we've reached the limit.
      break;
    }
  }

  return Status::OK;
}

Status OracleServer::GetCount(ServerContext* context,
                              const GraphsRequest* request, Count* response) {
  uint64_t count = 0;
  auto gen = m_oracle->GetUndirectedGraphsCount(
      Kind::All, std::make_shared<graph::undirected::algo::IsBipartite>());
  std::optional<size_t> opt_count;
  while ((opt_count = gen.Next())) {
    count += opt_count.value();
  }
  response->set_count(count);
  return Status::OK;
}
