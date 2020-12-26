#include "Game/AI/Action/actionPlayerWaterDivingJump.h"

namespace uking::action {

PlayerWaterDivingJump::PlayerWaterDivingJump(const InitArg& arg) : PlayerAction(arg) {}

PlayerWaterDivingJump::~PlayerWaterDivingJump() = default;

bool PlayerWaterDivingJump::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWaterDivingJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterDivingJump::leave_() {
    PlayerAction::leave_();
}

void PlayerWaterDivingJump::loadParams_() {
    getStaticParam(&mDiveSpeedF_s, "DiveSpeedF");
    getStaticParam(&mDiveHeight_s, "DiveHeight");
    getStaticParam(&mDiveSpeedDec_s, "DiveSpeedDec");
}

void PlayerWaterDivingJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
