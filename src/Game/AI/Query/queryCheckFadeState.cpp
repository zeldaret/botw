#include "Game/AI/Query/queryCheckFadeState.h"
#include <evfl/Query.h>

namespace uking::query {

CheckFadeState::CheckFadeState(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckFadeState::~CheckFadeState() = default;

// FIXME: implement
int CheckFadeState::doQuery() {
    return -1;
}

void CheckFadeState::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "FadeType");
    loadInt(arg.param_accessor, "State");
}

void CheckFadeState::loadParams() {
    getDynamicParam(&mFadeType, "FadeType");
    getDynamicParam(&mState, "State");
}

}  // namespace uking::query
