#include "Game/AI/Action/actionPlayerSitWait.h"

namespace uking::action {

PlayerSitWait::PlayerSitWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSitWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitWait::leave_() {
    PlayerAction::leave_();
}

void PlayerSitWait::loadParams_() {
    getStaticParam(&mAutoRecoverRate_s, "AutoRecoverRate");
    getStaticParam(&mEnergyAutoRecover_s, "EnergyAutoRecover");
}

void PlayerSitWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
