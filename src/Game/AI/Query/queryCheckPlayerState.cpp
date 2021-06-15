#include "Game/AI/Query/queryCheckPlayerState.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPlayerState::CheckPlayerState(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerState::~CheckPlayerState() = default;

// FIXME: implement
int CheckPlayerState::doQuery() {
    return -1;
}

void CheckPlayerState::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "PlayerState");
}

void CheckPlayerState::loadParams() {
    getDynamicParam(&mPlayerState, "PlayerState");
}

}  // namespace uking::query
