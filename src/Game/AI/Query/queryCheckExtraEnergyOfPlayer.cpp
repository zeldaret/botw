#include "Game/AI/Query/queryCheckExtraEnergyOfPlayer.h"
#include <evfl/Query.h>

namespace uking::query {

CheckExtraEnergyOfPlayer::CheckExtraEnergyOfPlayer(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckExtraEnergyOfPlayer::~CheckExtraEnergyOfPlayer() = default;

// FIXME: implement
int CheckExtraEnergyOfPlayer::doQuery() {
    return -1;
}

void CheckExtraEnergyOfPlayer::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void CheckExtraEnergyOfPlayer::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
