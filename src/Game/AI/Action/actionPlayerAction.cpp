#include "Game/AI/Action/actionPlayerAction.h"

namespace uking::action {

PlayerAction::PlayerAction(const InitArg& arg) : ActionEx(arg) {}

void PlayerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void PlayerAction::leave_() {
    ActionEx::leave_();
}

void PlayerAction::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
