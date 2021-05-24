#include "Game/AI/Query/queryCheckResultOfNPCConflict.h"
#include <evfl/Query.h>

namespace uking::query {

CheckResultOfNPCConflict::CheckResultOfNPCConflict(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckResultOfNPCConflict::~CheckResultOfNPCConflict() = default;

// FIXME: implement
int CheckResultOfNPCConflict::doQuery() {
    return -1;
}

void CheckResultOfNPCConflict::loadParams(const evfl::QueryArg& arg) {}

void CheckResultOfNPCConflict::loadParams() {}

}  // namespace uking::query
