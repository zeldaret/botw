#include "Game/AI/Action/actionForkNoWeaponAttackDirectParam.h"

namespace uking::action {

ForkNoWeaponAttackDirectParam::ForkNoWeaponAttackDirectParam(const InitArg& arg)
    : ForkNoWeaponAttack(arg) {}

ForkNoWeaponAttackDirectParam::~ForkNoWeaponAttackDirectParam() = default;

bool ForkNoWeaponAttackDirectParam::init_(sead::Heap* heap) {
    return ForkNoWeaponAttack::init_(heap);
}

void ForkNoWeaponAttackDirectParam::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttack::enter_(params);
}

void ForkNoWeaponAttackDirectParam::leave_() {
    ForkNoWeaponAttack::leave_();
}

void ForkNoWeaponAttackDirectParam::loadParams_() {
    ForkNoWeaponAttack::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mGuardBreakPower_s, "GuardBreakPower");
    getStaticParam(&mImpulse_s, "Impulse");
}

void ForkNoWeaponAttackDirectParam::calc_() {
    ForkNoWeaponAttack::calc_();
}

}  // namespace uking::action
