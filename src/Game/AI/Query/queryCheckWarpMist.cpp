#include "Game/AI/Query/queryCheckWarpMist.h"
#include <evfl/Query.h>

namespace uking::query {

CheckWarpMist::CheckWarpMist(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckWarpMist::~CheckWarpMist() = default;

// FIXME: implement
int CheckWarpMist::doQuery() {
    return -1;
}

void CheckWarpMist::loadParams(const evfl::QueryArg& arg) {}

void CheckWarpMist::loadParams() {}

}  // namespace uking::query
