#include "Game/AI/Action/actionPlayerDeadWait.h"

namespace uking::action {

PlayerDeadWait::PlayerDeadWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerDeadWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDeadWait::leave_() {
    PlayerAction::leave_();
}

void PlayerDeadWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
