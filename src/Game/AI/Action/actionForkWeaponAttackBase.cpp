#include "Game/AI/Action/actionForkWeaponAttackBase.h"

namespace uking::action {

ForkWeaponAttackBase::ForkWeaponAttackBase(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkWeaponAttackBase::~ForkWeaponAttackBase() = default;

bool ForkWeaponAttackBase::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkWeaponAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
}

void ForkWeaponAttackBase::leave_() {
    ForkAttackWithWeaponOrWithout::leave_();
}

void ForkWeaponAttackBase::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mIsNoRod_s, "IsNoRod");
}

void ForkWeaponAttackBase::calc_() {
    ForkAttackWithWeaponOrWithout::calc_();
}

}  // namespace uking::action
