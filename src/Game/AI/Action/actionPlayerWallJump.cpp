#include "Game/AI/Action/actionPlayerWallJump.h"

namespace uking::action {

PlayerWallJump::PlayerWallJump(const InitArg& arg) : PlayerAction(arg) {}

PlayerWallJump::~PlayerWallJump() = default;

bool PlayerWallJump::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallJump::leave_() {
    PlayerAction::leave_();
}

void PlayerWallJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
}

void PlayerWallJump::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
