#include "Game/AI/Query/queryCheckRoad.h"
#include <evfl/Query.h>

namespace uking::query {

CheckRoad::CheckRoad(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckRoad::~CheckRoad() = default;

// FIXME: implement
int CheckRoad::doQuery() {
    return -1;
}

void CheckRoad::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "RoadId");
}

void CheckRoad::loadParams() {
    getDynamicParam(&mRoadId, "RoadId");
}

}  // namespace uking::query
