#include "Game/AI/Action/actionPlayerBackJumpLand.h"

namespace uking::action {

PlayerBackJumpLand::PlayerBackJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBackJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBackJumpLand::leave_() {
    PlayerAction::leave_();
}

void PlayerBackJumpLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
