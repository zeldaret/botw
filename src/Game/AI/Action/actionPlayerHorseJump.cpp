#include "Game/AI/Action/actionPlayerHorseJump.h"

namespace uking::action {

PlayerHorseJump::PlayerHorseJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHorseJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHorseJump::leave_() {
    PlayerAction::leave_();
}

void PlayerHorseJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpSpeedF2_s, "JumpSpeedF2");
    getStaticParam(&mJumpSpeedF3_s, "JumpSpeedF3");
    getStaticParam(&mJumpSpeedF4_s, "JumpSpeedF4");
    getStaticParam(&mJumpMaxSpeedF_s, "JumpMaxSpeedF");
    getStaticParam(&mAimDistOffset_s, "AimDistOffset");
    getDynamicParam(&mJumpGear_d, "JumpGear");
    getDynamicParam(&mIsLargeHorse_d, "IsLargeHorse");
}

void PlayerHorseJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
