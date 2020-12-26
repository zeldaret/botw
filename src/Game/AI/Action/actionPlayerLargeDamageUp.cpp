#include "Game/AI/Action/actionPlayerLargeDamageUp.h"

namespace uking::action {

PlayerLargeDamageUp::PlayerLargeDamageUp(const InitArg& arg) : PlayerAction(arg) {}

PlayerLargeDamageUp::~PlayerLargeDamageUp() = default;

bool PlayerLargeDamageUp::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLargeDamageUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLargeDamageUp::leave_() {
    PlayerAction::leave_();
}

void PlayerLargeDamageUp::loadParams_() {}

void PlayerLargeDamageUp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
