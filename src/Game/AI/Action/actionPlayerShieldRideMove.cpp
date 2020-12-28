#include "Game/AI/Action/actionPlayerShieldRideMove.h"

namespace uking::action {

PlayerShieldRideMove::PlayerShieldRideMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerShieldRideMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerShieldRideMove::leave_() {
    PlayerAction::leave_();
}

void PlayerShieldRideMove::loadParams_() {
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mContJumpSpeedF_s, "ContJumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mContJumpInterval_s, "ContJumpInterval");
    getStaticParam(&mShieldBreakHeight_s, "ShieldBreakHeight");
    getStaticParam(&mFinishSpeed_s, "FinishSpeed");
    getStaticParam(&mMaxJumpSpeed_s, "MaxJumpSpeed");
    getStaticParam(&mLandSEOnInAirFrame_s, "LandSEOnInAirFrame");
}

void PlayerShieldRideMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
