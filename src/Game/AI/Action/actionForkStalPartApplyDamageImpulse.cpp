#include "Game/AI/Action/actionForkStalPartApplyDamageImpulse.h"

namespace uking::action {

ForkStalPartApplyDamageImpulse::ForkStalPartApplyDamageImpulse(const InitArg& arg) : Fork(arg) {}

ForkStalPartApplyDamageImpulse::~ForkStalPartApplyDamageImpulse() = default;

bool ForkStalPartApplyDamageImpulse::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkStalPartApplyDamageImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkStalPartApplyDamageImpulse::leave_() {
    Fork::leave_();
}

void ForkStalPartApplyDamageImpulse::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mMaxAddSpeed_s, "MaxAddSpeed");
    getStaticParam(&mSwordRate_s, "SwordRate");
    getStaticParam(&mSpearRate_s, "SpearRate");
    getStaticParam(&mLswordRate_s, "LswordRate");
    getStaticParam(&mArrowRate_s, "ArrowRate");
    getStaticParam(&mBombRate_s, "BombRate");
    getStaticParam(&mGustRate_s, "GustRate");
    getStaticParam(&mLargeAttackAddRate_s, "LargeAttackAddRate");
    getStaticParam(&mMaxAddSpeedY_s, "MaxAddSpeedY");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRotAccMaxSpeedRatio_s, "RotAccMaxSpeedRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsViewHitDir_s, "IsViewHitDir");
}

void ForkStalPartApplyDamageImpulse::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
