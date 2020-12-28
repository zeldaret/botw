#include "Game/AI/Action/actionPlayerIce.h"

namespace uking::action {

PlayerIce::PlayerIce(const InitArg& arg) : PlayerAction(arg) {}

void PlayerIce::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIce::leave_() {
    PlayerAction::leave_();
}

void PlayerIce::loadParams_() {
    getStaticParam(&mEnergyIce_s, "EnergyIce");
    getStaticParam(&mCountRate_s, "CountRate");
    getStaticParam(&mInputInterval_s, "InputInterval");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedFBlowOff_s, "JumpSpeedFBlowOff");
    getStaticParam(&mJumpHeightBlowOff_s, "JumpHeightBlowOff");
}

void PlayerIce::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
