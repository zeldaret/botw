#include "Game/AI/Action/actionPlayerMove.h"

namespace uking::action {

PlayerMove::PlayerMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerMove::leave_() {
    PlayerAction::leave_();
}

void PlayerMove::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
    getStaticParam(&mForceApplyPushAnm_s, "ForceApplyPushAnm");
    getStaticParam(&mEnergyDashTrig_s, "EnergyDashTrig");
    getStaticParam(&mPushContinueTime_s, "PushContinueTime");
    getStaticParam(&mPushStopDistY_s, "PushStopDistY");
    getStaticParam(&mInvalidFallFrame_s, "InvalidFallFrame");
}

void PlayerMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
