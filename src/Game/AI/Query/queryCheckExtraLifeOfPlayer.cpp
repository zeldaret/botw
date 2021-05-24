#include "Game/AI/Query/queryCheckExtraLifeOfPlayer.h"
#include <evfl/Query.h>

namespace uking::query {

CheckExtraLifeOfPlayer::CheckExtraLifeOfPlayer(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckExtraLifeOfPlayer::~CheckExtraLifeOfPlayer() = default;

// FIXME: implement
int CheckExtraLifeOfPlayer::doQuery() {
    return -1;
}

void CheckExtraLifeOfPlayer::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void CheckExtraLifeOfPlayer::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
