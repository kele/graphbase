#include "bins/oracle/server/server.hpp"

#include <memory>

#include <grpc++/grpc++.h>

#include "conversions/undirected.hpp"
#include "graph/algo/undirected_predicates.hpp"
#include "oracle/oracle.hpp"
#include "oracle/process_request.hpp"
#include "protos/graph.pb.h"
#include "protos/sv_oracle.grpc.pb.h"

using namespace grpc;
using namespace graphbase;

using GraphProto = protos::Graph;
using GraphsRequestProto = protos::services::GraphsRequest;

////////////////////////////////////////////////////////////////////////////////
// OracleServer implementation

OracleServer::OracleServer(std::unique_ptr<graphbase::Oracle> oracle)
    : m_oracle(std::move(oracle)) {}

Status OracleServer::GetGraphs(ServerContext* context,
                               const GraphsRequestProto* request,
                               ServerWriter<GraphProto>* writer) try {
  using graph::undirected::BasicGraph;

  auto gen = m_oracle->GetUndirectedGraphs(KindFromRequest(request),
                                           PredicateFromRequest(request));

  size_t limit = request->limit();
  size_t count = 0;

  std::optional<std::shared_ptr<const BasicGraph>> opt_g;
  while ((opt_g = gen.next())) {
    const BasicGraph& g = *opt_g.value();
    GraphProto response;
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

} catch (const std::exception& e) {
  return Status(StatusCode::INTERNAL, e.what());
}

Status OracleServer::GetCount(ServerContext* context,
                              const GraphsRequestProto* request,
                              protos::services::Count* response) try {
  uint64_t count = 0;
  auto gen = m_oracle->GetUndirectedGraphsCount(KindFromRequest(request),
                                                PredicateFromRequest(request));

  std::optional<size_t> opt_count;
  while ((opt_count = gen.next())) {
    count += opt_count.value();
  }
  response->set_count(count);
  return Status::OK;

} catch (const std::exception& e) {
  return Status(StatusCode::INTERNAL, e.what());
}
