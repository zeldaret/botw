#include "Game/AI/Action/actionAttackPowerExplode.h"

namespace uking::action {

AttackPowerExplode::AttackPowerExplode(const InitArg& arg) : Explode(arg) {}

AttackPowerExplode::~AttackPowerExplode() = default;

bool AttackPowerExplode::init_(sead::Heap* heap) {
    return Explode::init_(heap);
}

void AttackPowerExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    Explode::enter_(params);
}

void AttackPowerExplode::leave_() {
    Explode::leave_();
}

void AttackPowerExplode::loadParams_() {
    Explode::loadParams_();
    getDynamicParam(&mIsPlayerAttack_d, "IsPlayerAttack");
}

void AttackPowerExplode::calc_() {
    Explode::calc_();
}

}  // namespace uking::action
