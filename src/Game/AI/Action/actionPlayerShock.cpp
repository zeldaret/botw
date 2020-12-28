#include "Game/AI/Action/actionPlayerShock.h"

namespace uking::action {

PlayerShock::PlayerShock(const InitArg& arg) : PlayerAction(arg) {}

void PlayerShock::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerShock::leave_() {
    PlayerAction::leave_();
}

void PlayerShock::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
