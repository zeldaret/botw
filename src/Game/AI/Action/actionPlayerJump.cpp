#include "Game/AI/Action/actionPlayerJump.h"

namespace uking::action {

PlayerJump::PlayerJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerJump::leave_() {
    PlayerAction::leave_();
}

void PlayerJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightAddByAngle_s, "JumpHeightAddByAngle");
    getStaticParam(&mJumpHeightAddBySpeed_s, "JumpHeightAddBySpeed");
    getStaticParam(&mJumpHeightMaxDecRateByWater_s, "JumpHeightMaxDecRateByWater");
    getStaticParam(&mIgnoreWaterHeight_s, "IgnoreWaterHeight");
    getStaticParam(&mEnergyJump_s, "EnergyJump");
    getStaticParam(&mEnergyDashJump_s, "EnergyDashJump");
    getStaticParam(&mEnergyUseDiam1_s, "EnergyUseDiam1");
    getStaticParam(&mEnergyUseDiam2_s, "EnergyUseDiam2");
    getStaticParam(&mEnergyUseDiam3_s, "EnergyUseDiam3");
}

void PlayerJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
