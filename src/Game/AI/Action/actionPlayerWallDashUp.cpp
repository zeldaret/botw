#include "Game/AI/Action/actionPlayerWallDashUp.h"

namespace uking::action {

PlayerWallDashUp::PlayerWallDashUp(const InitArg& arg) : PlayerAction(arg) {}

PlayerWallDashUp::~PlayerWallDashUp() = default;

bool PlayerWallDashUp::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWallDashUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallDashUp::leave_() {
    PlayerAction::leave_();
}

void PlayerWallDashUp::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mMinSpeedF_s, "MinSpeedF");
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
}

void PlayerWallDashUp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
