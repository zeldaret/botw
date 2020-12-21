#include "Game/AI/Query/queryCheckGetDemoTypeFromArg.h"
#include <evfl/query.h>

namespace uking::query {

CheckGetDemoTypeFromArg::CheckGetDemoTypeFromArg(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckGetDemoTypeFromArg::~CheckGetDemoTypeFromArg() = default;

// FIXME: implement
int CheckGetDemoTypeFromArg::doQuery() {
    return -1;
}

void CheckGetDemoTypeFromArg::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "UseLastTryGetItemName");
    loadString(arg.param_accessor, "CheckTargetActorName");
}

void CheckGetDemoTypeFromArg::loadParams() {
    getDynamicParam(&mUseLastTryGetItemName, "UseLastTryGetItemName");
    getDynamicParam(&mCheckTargetActorName, "CheckTargetActorName");
}

}  // namespace uking::query
