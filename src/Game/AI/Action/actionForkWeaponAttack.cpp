#include "Game/AI/Action/actionForkWeaponAttack.h"

namespace uking::action {

ForkWeaponAttack::ForkWeaponAttack(const InitArg& arg) : ForkWeaponAttackBase(arg) {}

ForkWeaponAttack::~ForkWeaponAttack() = default;

void ForkWeaponAttack::loadParams_() {
    ForkWeaponAttackBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::action
