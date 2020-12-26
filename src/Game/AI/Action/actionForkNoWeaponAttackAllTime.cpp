#include "Game/AI/Action/actionForkNoWeaponAttackAllTime.h"

namespace uking::action {

ForkNoWeaponAttackAllTime::ForkNoWeaponAttackAllTime(const InitArg& arg)
    : ForkNoWeaponAttackBase(arg) {}

ForkNoWeaponAttackAllTime::~ForkNoWeaponAttackAllTime() = default;

bool ForkNoWeaponAttackAllTime::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackBase::init_(heap);
}

void ForkNoWeaponAttackAllTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackBase::enter_(params);
}

void ForkNoWeaponAttackAllTime::leave_() {
    ForkNoWeaponAttackBase::leave_();
}

void ForkNoWeaponAttackAllTime::loadParams_() {
    ForkNoWeaponAttackBase::loadParams_();
    getStaticParam(&mAtDirString_s, "AtDirString");
}

void ForkNoWeaponAttackAllTime::calc_() {
    ForkNoWeaponAttackBase::calc_();
}

}  // namespace uking::action
