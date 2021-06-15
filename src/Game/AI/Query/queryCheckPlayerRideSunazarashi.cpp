#include "Game/AI/Query/queryCheckPlayerRideSunazarashi.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerRideSunazarashi::CheckPlayerRideSunazarashi(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckPlayerRideSunazarashi::~CheckPlayerRideSunazarashi() = default;

// FIXME: implement
int CheckPlayerRideSunazarashi::doQuery() {
    return -1;
}

void CheckPlayerRideSunazarashi::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "SunazarashiType");
    loadString(arg.param_accessor, "SunazarashiName");
}

void CheckPlayerRideSunazarashi::loadParams() {
    getDynamicParam(&mSunazarashiType, "SunazarashiType");
    getDynamicParam(&mSunazarashiName, "SunazarashiName");
}

}  // namespace uking::query
