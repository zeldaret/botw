#include "Game/AI/Action/actionForkWeaponAttack.h"

namespace uking::action {

ForkWeaponAttack::ForkWeaponAttack(const InitArg& arg) : ForkWeaponAttackBase(arg) {}

ForkWeaponAttack::~ForkWeaponAttack() = default;

bool ForkWeaponAttack::init_(sead::Heap* heap) {
    return ForkWeaponAttackBase::init_(heap);
}

void ForkWeaponAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponAttackBase::enter_(params);
}

void ForkWeaponAttack::leave_() {
    ForkWeaponAttackBase::leave_();
}

void ForkWeaponAttack::loadParams_() {
    ForkWeaponAttackBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void ForkWeaponAttack::calc_() {
    ForkWeaponAttackBase::calc_();
}

}  // namespace uking::action
