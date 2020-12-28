#include "Game/AI/Action/actionPlayerLargeDamageUp.h"

namespace uking::action {

PlayerLargeDamageUp::PlayerLargeDamageUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLargeDamageUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLargeDamageUp::leave_() {
    PlayerAction::leave_();
}

void PlayerLargeDamageUp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
