#include "Game/AI/Action/actionPlayerStepMove.h"

namespace uking::action {

PlayerStepMove::PlayerStepMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStepMove::leave_() {
    PlayerAction::leave_();
}

void PlayerStepMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
