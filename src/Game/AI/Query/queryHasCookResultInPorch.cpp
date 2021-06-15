#include "Game/AI/Query/queryHasCookResultInPorch.h"
#include <evfl/Query.h>

namespace uking::query {

HasCookResultInPorch::HasCookResultInPorch(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasCookResultInPorch::~HasCookResultInPorch() = default;

// FIXME: implement
int HasCookResultInPorch::doQuery() {
    return -1;
}

void HasCookResultInPorch::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Count");
    loadString(arg.param_accessor, "PorchItemName");
    loadString(arg.param_accessor, "CookEffectType");
}

void HasCookResultInPorch::loadParams() {
    getDynamicParam(&mCount, "Count");
    getDynamicParam(&mPorchItemName, "PorchItemName");
    getDynamicParam(&mCookEffectType, "CookEffectType");
}

}  // namespace uking::query
