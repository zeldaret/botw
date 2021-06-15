#include "Game/AI/Query/queryCheckCookResultStatus.h"
#include <evfl/Query.h>

namespace uking::query {

CheckCookResultStatus::CheckCookResultStatus(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckCookResultStatus::~CheckCookResultStatus() = default;

// FIXME: implement
int CheckCookResultStatus::doQuery() {
    return -1;
}

void CheckCookResultStatus::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckType");
}

void CheckCookResultStatus::loadParams() {
    getDynamicParam(&mCheckType, "CheckType");
    getAITreeVariable(&mCurrentCookResultHolder, "CurrentCookResultHolder");
}

}  // namespace uking::query
