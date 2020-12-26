#include "Game/AI/Action/actionForkNoWeaponAttackBase.h"

namespace uking::action {

ForkNoWeaponAttackBase::ForkNoWeaponAttackBase(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkNoWeaponAttackBase::~ForkNoWeaponAttackBase() = default;

bool ForkNoWeaponAttackBase::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkNoWeaponAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
}

void ForkNoWeaponAttackBase::leave_() {
    ForkAttackWithWeaponOrWithout::leave_();
}

void ForkNoWeaponAttackBase::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mAttackPowerScale_s, "AttackPowerScale");
    getStaticParam(&mIsUseAttackParam_s, "IsUseAttackParam");
    // FIXME: CALL _ZN4sead17StringBuilderBaseIcE6formatEPKcz @ 0x7100b0d550
    // FIXME: CALL _ZN4sead17StringBuilderBaseIcE6formatEPKcz @ 0x7100b0d550
    // FIXME: CALL _ZN4sead17StringBuilderBaseIcE6formatEPKcz @ 0x7100b0d550
    getStaticParam(&mChmName1_s, "ChmName1");
}

void ForkNoWeaponAttackBase::calc_() {
    ForkAttackWithWeaponOrWithout::calc_();
}

}  // namespace uking::action
