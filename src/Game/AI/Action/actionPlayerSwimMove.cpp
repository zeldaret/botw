#include "Game/AI/Action/actionPlayerSwimMove.h"

namespace uking::action {

PlayerSwimMove::PlayerSwimMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimMove::leave_() {
    PlayerAction::leave_();
}

void PlayerSwimMove::loadParams_() {
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
    getStaticParam(&mMaxSpeedS_s, "MaxSpeedS");
    getStaticParam(&mMaxSpeedB_s, "MaxSpeedB");
    getStaticParam(&mMaxSpeedDash_s, "MaxSpeedDash");
    getStaticParam(&mEnergyMove_s, "EnergyMove");
    getStaticParam(&mEnergyDash_s, "EnergyDash");
    getStaticParam(&mDecSpeedRate_s, "DecSpeedRate");
}

void PlayerSwimMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
