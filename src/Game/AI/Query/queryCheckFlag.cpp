#include "Game/AI/Query/queryCheckFlag.h"
#include <evfl/query.h>

namespace uking::query {

CheckFlag::CheckFlag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckFlag::~CheckFlag() = default;

// FIXME: implement
int CheckFlag::doQuery() {
    return -1;
}

void CheckFlag::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "FlagName");
}

void CheckFlag::loadParams() {
    getDynamicParam(&mFlagName, "FlagName");
}

}  // namespace uking::query
