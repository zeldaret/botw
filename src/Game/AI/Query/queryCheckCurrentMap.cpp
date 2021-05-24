#include "Game/AI/Query/queryCheckCurrentMap.h"
#include <evfl/Query.h>

namespace uking::query {

CheckCurrentMap::CheckCurrentMap(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckCurrentMap::~CheckCurrentMap() = default;

// FIXME: implement
int CheckCurrentMap::doQuery() {
    return -1;
}

void CheckCurrentMap::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "MapName");
}

void CheckCurrentMap::loadParams() {
    getDynamicParam(&mMapName, "MapName");
}

}  // namespace uking::query
