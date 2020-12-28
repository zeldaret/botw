#include "Game/AI/Action/actionPlayerStepAttack.h"

namespace uking::action {

PlayerStepAttack::PlayerStepAttack(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStepAttack::leave_() {
    PlayerAction::leave_();
}

void PlayerStepAttack::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerStepAttack::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
