#include "Game/AI/Action/actionPlayerGuardJustFall.h"

namespace uking::action {

PlayerGuardJustFall::PlayerGuardJustFall(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardJustFall::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuardJustFall::leave_() {
    PlayerAction::leave_();
}

void PlayerGuardJustFall::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
