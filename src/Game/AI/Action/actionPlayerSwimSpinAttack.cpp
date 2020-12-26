#include "Game/AI/Action/actionPlayerSwimSpinAttack.h"

namespace uking::action {

PlayerSwimSpinAttack::PlayerSwimSpinAttack(const InitArg& arg) : PlayerAction(arg) {}

PlayerSwimSpinAttack::~PlayerSwimSpinAttack() = default;

bool PlayerSwimSpinAttack::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSwimSpinAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimSpinAttack::leave_() {
    PlayerAction::leave_();
}

void PlayerSwimSpinAttack::loadParams_() {
    getStaticParam(&mEnergyDash_s, "EnergyDash");
}

void PlayerSwimSpinAttack::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
