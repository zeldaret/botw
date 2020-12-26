#include "Game/AI/Action/actionPlayerSquatMove.h"

namespace uking::action {

PlayerSquatMove::PlayerSquatMove(const InitArg& arg) : PlayerAction(arg) {}

PlayerSquatMove::~PlayerSquatMove() = default;

bool PlayerSquatMove::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSquatMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSquatMove::leave_() {
    PlayerAction::leave_();
}

void PlayerSquatMove::loadParams_() {}

void PlayerSquatMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
