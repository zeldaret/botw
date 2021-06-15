#include "Game/AI/Query/queryCheckMapArea.h"
#include <evfl/Query.h>

namespace uking::query {

CheckMapArea::CheckMapArea(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMapArea::~CheckMapArea() = default;

// FIXME: implement
int CheckMapArea::doQuery() {
    return -1;
}

void CheckMapArea::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "MapAreaName");
}

void CheckMapArea::loadParams() {
    getDynamicParam(&mMapAreaName, "MapAreaName");
}

}  // namespace uking::query
