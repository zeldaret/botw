#include "Game/AI/Action/actionPlayerStepMove.h"

namespace uking::action {

PlayerStepMove::PlayerStepMove(const InitArg& arg) : PlayerAction(arg) {}

PlayerStepMove::~PlayerStepMove() = default;

bool PlayerStepMove::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStepMove::leave_() {
    PlayerAction::leave_();
}

void PlayerStepMove::loadParams_() {}

void PlayerStepMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
