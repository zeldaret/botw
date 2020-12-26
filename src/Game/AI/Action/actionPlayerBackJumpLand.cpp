#include "Game/AI/Action/actionPlayerBackJumpLand.h"

namespace uking::action {

PlayerBackJumpLand::PlayerBackJumpLand(const InitArg& arg) : PlayerAction(arg) {}

PlayerBackJumpLand::~PlayerBackJumpLand() = default;

bool PlayerBackJumpLand::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerBackJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBackJumpLand::leave_() {
    PlayerAction::leave_();
}

void PlayerBackJumpLand::loadParams_() {}

void PlayerBackJumpLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
