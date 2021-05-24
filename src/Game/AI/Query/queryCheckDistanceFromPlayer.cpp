#include "Game/AI/Query/queryCheckDistanceFromPlayer.h"
#include <evfl/Query.h>

namespace uking::query {

CheckDistanceFromPlayer::CheckDistanceFromPlayer(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDistanceFromPlayer::~CheckDistanceFromPlayer() = default;

// FIXME: implement
int CheckDistanceFromPlayer::doQuery() {
    return -1;
}

void CheckDistanceFromPlayer::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "Border");
}

void CheckDistanceFromPlayer::loadParams() {
    getDynamicParam(&mBorder, "Border");
}

}  // namespace uking::query
