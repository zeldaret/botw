#include "Game/AI/Action/actionPlayerWallSlip.h"

namespace uking::action {

PlayerWallSlip::PlayerWallSlip(const InitArg& arg) : PlayerAction(arg) {}

PlayerWallSlip::~PlayerWallSlip() = default;

bool PlayerWallSlip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWallSlip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallSlip::leave_() {
    PlayerAction::leave_();
}

void PlayerWallSlip::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerWallSlip::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
