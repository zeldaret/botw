#include "Game/Actor/Action/actionChuchuPreAttack.h"

namespace uking::action {

ChuchuPreAttack::ChuchuPreAttack(const InitArg& arg) : GelJumpBase(arg) {}

ChuchuPreAttack::~ChuchuPreAttack() = default;

bool ChuchuPreAttack::init_(sead::Heap* heap) {
    return GelJumpBase::init_(heap);
}

void ChuchuPreAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GelJumpBase::enter_(params);
}

void ChuchuPreAttack::leave_() {
    GelJumpBase::leave_();
}

void ChuchuPreAttack::loadParams_() {
    GelJumpBase::loadParams_();
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
    GelJumpBase::calc_();
}

}  // namespace uking::action
