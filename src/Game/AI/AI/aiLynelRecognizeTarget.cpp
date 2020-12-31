#include "Game/AI/AI/aiLynelRecognizeTarget.h"

namespace uking::ai {

LynelRecognizeTarget::LynelRecognizeTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRecognizeTarget::~LynelRecognizeTarget() = default;

bool LynelRecognizeTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelRecognizeTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelRecognizeTarget::loadParams_() {
    getStaticParam(&mAttensionStartPoint_s, "AttensionStartPoint");
    getStaticParam(&mObserveEndPoint_s, "ObserveEndPoint");
    getStaticParam(&mDrawnWeaponPoint_s, "DrawnWeaponPoint");
    getStaticParam(&mWeaponAimPoint_s, "WeaponAimPoint");
    getStaticParam(&mAttackPoint_s, "AttackPoint");
    getStaticParam(&mDashPoint_s, "DashPoint");
    getStaticParam(&mAppPoint_s, "AppPoint");
    getStaticParam(&mHorseRidePoint_s, "HorseRidePoint");
    getStaticParam(&mDamagePoint_s, "DamagePoint");
    getStaticParam(&mTrickedMaskPoint_s, "TrickedMaskPoint");
    getStaticParam(&mBombPoint_s, "BombPoint");
    getStaticParam(&mAimPoint_s, "AimPoint");
    getStaticParam(&mNearDistPoint_s, "NearDistPoint");
    getStaticParam(&mMiddleDistPoint_s, "MiddleDistPoint");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mTiredPoint_s, "TiredPoint");
    getStaticParam(&mForceBattleStartTime_s, "ForceBattleStartTime");
    getStaticParam(&mNearDistance_s, "NearDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mAimAngle_s, "AimAngle");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
}

}  // namespace uking::ai
