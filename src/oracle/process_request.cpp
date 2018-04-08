#include "oracle/process_request.hpp"

#include <memory>

#include "graph/algo/undirected_predicates.hpp"

using GraphsRequestProto = protos::services::GraphsRequest;

std::shared_ptr<graph::predicates::Predicate> PredicateFromRequest(
    const GraphsRequestProto* request) {
  switch (request->predicate().predicate_case()) {
    case protos::services::Predicate::kIsBipartite:
      return std::make_shared<graph::undirected::predicates::IsBipartite>();
    default:
      throw std::runtime_error("Unrecognized predicate.");
  }
}

using graphbase::graphsource::Kind;
Kind KindFromRequest(const GraphsRequestProto* request) { return Kind::All; }
