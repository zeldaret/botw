#include "Game/AI/Query/queryCheckMiniGameTime.h"
#include <evfl/Query.h>

namespace uking::query {

CheckMiniGameTime::CheckMiniGameTime(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMiniGameTime::~CheckMiniGameTime() = default;

// FIXME: implement
int CheckMiniGameTime::doQuery() {
    return -1;
}

void CheckMiniGameTime::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Minute");
    loadInt(arg.param_accessor, "Second");
    loadInt(arg.param_accessor, "ConditionType");
}

void CheckMiniGameTime::loadParams() {
    getDynamicParam(&mMinute, "Minute");
    getDynamicParam(&mSecond, "Second");
    getDynamicParam(&mConditionType, "ConditionType");
}

}  // namespace uking::query
