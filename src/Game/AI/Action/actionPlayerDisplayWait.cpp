#include "Game/AI/Action/actionPlayerDisplayWait.h"

namespace uking::action {

PlayerDisplayWait::PlayerDisplayWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDisplayWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDisplayWait::leave_() {
    PlayerAction::leave_();
}

void PlayerDisplayWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
