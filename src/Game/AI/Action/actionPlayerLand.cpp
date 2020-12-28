#include "Game/AI/Action/actionPlayerLand.h"

namespace uking::action {

PlayerLand::PlayerLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLand::leave_() {
    PlayerAction::leave_();
}

void PlayerLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
