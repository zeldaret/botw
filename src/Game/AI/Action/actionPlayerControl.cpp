#include "Game/AI/Action/actionPlayerControl.h"

namespace uking::action {

PlayerControl::PlayerControl(const InitArg& arg) : PlayerAction(arg) {}

void PlayerControl::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerControl::leave_() {
    PlayerAction::leave_();
}

void PlayerControl::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
