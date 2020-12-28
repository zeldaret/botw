#include "Game/AI/Action/actionPlayerWait.h"

namespace uking::action {

PlayerWait::PlayerWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWait::leave_() {
    PlayerAction::leave_();
}

void PlayerWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
