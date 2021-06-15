#include "Game/AI/Query/queryCheckElapsedTimeOfMiniGame.h"
#include <evfl/Query.h>

namespace uking::query {

CheckElapsedTimeOfMiniGame::CheckElapsedTimeOfMiniGame(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckElapsedTimeOfMiniGame::~CheckElapsedTimeOfMiniGame() = default;

// FIXME: implement
int CheckElapsedTimeOfMiniGame::doQuery() {
    return -1;
}

void CheckElapsedTimeOfMiniGame::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void CheckElapsedTimeOfMiniGame::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
