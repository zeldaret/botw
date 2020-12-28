#include "Game/AI/Action/actionPlayerCaught.h"

namespace uking::action {

PlayerCaught::PlayerCaught(const InitArg& arg) : PlayerAction(arg) {}

PlayerCaught::~PlayerCaught() = default;

void PlayerCaught::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCaught::leave_() {
    PlayerAction::leave_();
}

void PlayerCaught::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
