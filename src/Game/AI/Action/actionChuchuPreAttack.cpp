#include "Game/AI/Action/actionChuchuPreAttack.h"

namespace uking::action {

ChuchuPreAttack::ChuchuPreAttack(const InitArg& arg) : ChuchuPreAttackBase(arg) {}

ChuchuPreAttack::~ChuchuPreAttack() = default;

bool ChuchuPreAttack::init_(sead::Heap* heap) {
    return ChuchuPreAttackBase::init_(heap);
}

void ChuchuPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ChuchuPreAttackBase::enter_(params);
}

void ChuchuPreAttack::leave_() {
    ChuchuPreAttackBase::leave_();
}

void ChuchuPreAttack::loadParams_() {
    ChuchuPreAttackBase::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mHitImpactForceSmallSwordS_s, "HitImpactForceSmallSwordS");
    getStaticParam(&mHitImpactForceSmallSwordL_s, "HitImpactForceSmallSwordL");
    getStaticParam(&mHitImpactForceLargeSwordS_s, "HitImpactForceLargeSwordS");
    getStaticParam(&mHitImpactForceLargeSwordL_s, "HitImpactForceLargeSwordL");
    getStaticParam(&mHitImpactForceSpearS_s, "HitImpactForceSpearS");
    getStaticParam(&mHitImpactForceSpearL_s, "HitImpactForceSpearL");
    getStaticParam(&mPosReduceRatioByDamage_s, "PosReduceRatioByDamage");
    getStaticParam(&mDamageAS_s, "DamageAS");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mLeaveSubAS_s, "LeaveSubAS");
    getStaticParam(&mDamageSubAS_s, "DamageSubAS");
}

void ChuchuPreAttack::calc_() {
    ChuchuPreAttackBase::calc_();
}

}  // namespace uking::action
