#include "Game/AI/Action/actionPlayerWaterFallJump.h"

namespace uking::action {

PlayerWaterFallJump::PlayerWaterFallJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWaterFallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterFallJump::leave_() {
    PlayerAction::leave_();
}

void PlayerWaterFallJump::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightWaterRemain_s, "JumpHeightWaterRemain");
    getStaticParam(&mJumpHeightWithZora_s, "JumpHeightWithZora");
}

void PlayerWaterFallJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
