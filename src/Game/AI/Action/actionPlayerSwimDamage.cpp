#include "Game/AI/Action/actionPlayerSwimDamage.h"

namespace uking::action {

PlayerSwimDamage::PlayerSwimDamage(const InitArg& arg) : PlayerAction(arg) {}

PlayerSwimDamage::~PlayerSwimDamage() = default;

bool PlayerSwimDamage::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSwimDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimDamage::leave_() {
    PlayerAction::leave_();
}

void PlayerSwimDamage::loadParams_() {}

void PlayerSwimDamage::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
