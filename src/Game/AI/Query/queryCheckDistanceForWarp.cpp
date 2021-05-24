#include "Game/AI/Query/queryCheckDistanceForWarp.h"
#include <evfl/Query.h>

namespace uking::query {

CheckDistanceForWarp::CheckDistanceForWarp(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDistanceForWarp::~CheckDistanceForWarp() = default;

// FIXME: implement
int CheckDistanceForWarp::doQuery() {
    return -1;
}

void CheckDistanceForWarp::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "WarpDestMapName");
    loadString(arg.param_accessor, "WarpDestPosName");
}

void CheckDistanceForWarp::loadParams() {
    getDynamicParam(&mWarpDestMapName, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName, "WarpDestPosName");
}

}  // namespace uking::query
