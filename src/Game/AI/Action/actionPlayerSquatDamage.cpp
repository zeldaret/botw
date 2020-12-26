#include "Game/AI/Action/actionPlayerSquatDamage.h"

namespace uking::action {

PlayerSquatDamage::PlayerSquatDamage(const InitArg& arg) : PlayerAction(arg) {}

PlayerSquatDamage::~PlayerSquatDamage() = default;

bool PlayerSquatDamage::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSquatDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSquatDamage::leave_() {
    PlayerAction::leave_();
}

void PlayerSquatDamage::loadParams_() {}

void PlayerSquatDamage::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
