#pragma once

#include "graph/algo/predicates.hpp"
#include "graphsource/kinds.hpp"
#include "protos/sv_oracle.grpc.pb.h"

using namespace graphbase;

graphbase::graphsource::Kind
KindFromRequest(const protos::services::GraphsRequest *request);

std::shared_ptr<graph::predicates::Predicate>
PredicateFromRequest(const protos::services::GraphsRequest *request);
