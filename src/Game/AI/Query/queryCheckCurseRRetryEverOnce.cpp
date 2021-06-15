#include "Game/AI/Query/queryCheckCurseRRetryEverOnce.h"
#include <evfl/Query.h>

namespace uking::query {

CheckCurseRRetryEverOnce::CheckCurseRRetryEverOnce(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckCurseRRetryEverOnce::~CheckCurseRRetryEverOnce() = default;

// FIXME: implement
int CheckCurseRRetryEverOnce::doQuery() {
    return -1;
}

void CheckCurseRRetryEverOnce::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CurseRType");
}

void CheckCurseRRetryEverOnce::loadParams() {
    getDynamicParam(&mCurseRType, "CurseRType");
}

}  // namespace uking::query
