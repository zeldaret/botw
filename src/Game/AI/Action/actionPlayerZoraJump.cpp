#include "Game/AI/Action/actionPlayerZoraJump.h"

namespace uking::action {

PlayerZoraJump::PlayerZoraJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerZoraJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerZoraJump::leave_() {
    PlayerAction::leave_();
}

void PlayerZoraJump::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PlayerZoraJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
