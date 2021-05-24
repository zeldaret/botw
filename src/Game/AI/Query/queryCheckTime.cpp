#include "Game/AI/Query/queryCheckTime.h"
#include <evfl/Query.h>

namespace uking::query {

CheckTime::CheckTime(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckTime::~CheckTime() = default;

// FIXME: implement
int CheckTime::doQuery() {
    return -1;
}

void CheckTime::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Hour");
    loadInt(arg.param_accessor, "Minute");
    loadString(arg.param_accessor, "ConditionType");
}

void CheckTime::loadParams() {
    getDynamicParam(&mHour, "Hour");
    getDynamicParam(&mMinute, "Minute");
    getDynamicParam(&mConditionType, "ConditionType");
}

}  // namespace uking::query
