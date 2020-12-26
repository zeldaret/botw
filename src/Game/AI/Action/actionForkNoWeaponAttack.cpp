#include "Game/AI/Action/actionForkNoWeaponAttack.h"

namespace uking::action {

ForkNoWeaponAttack::ForkNoWeaponAttack(const InitArg& arg) : ForkNoWeaponAttackBase(arg) {}

ForkNoWeaponAttack::~ForkNoWeaponAttack() = default;

bool ForkNoWeaponAttack::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackBase::init_(heap);
}

void ForkNoWeaponAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackBase::enter_(params);
}

void ForkNoWeaponAttack::leave_() {
    ForkNoWeaponAttackBase::leave_();
}

void ForkNoWeaponAttack::loadParams_() {
    ForkNoWeaponAttackBase::loadParams_();
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mSeqBank_s, "SeqBank");
}

void ForkNoWeaponAttack::calc_() {
    ForkNoWeaponAttackBase::calc_();
}

}  // namespace uking::action
