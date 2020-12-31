#include "Game/AI/AI/aiEnemyNoiseTarget.h"

namespace uking::ai {

EnemyNoiseTarget::EnemyNoiseTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoiseTarget::~EnemyNoiseTarget() = default;

bool EnemyNoiseTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNoiseTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoiseTarget::loadParams_() {
    getStaticParam(&mLostTime_s, "LostTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRerouteTimeMin_s, "RerouteTimeMin");
    getStaticParam(&mRerouteTimeMax_s, "RerouteTimeMax");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mUnReachableToRepathDist_s, "UnReachableToRepathDist");
    getStaticParam(&mNoShieldEquipWpIdx_s, "NoShieldEquipWpIdx");
    getStaticParam(&mTooFarPathDist_s, "TooFarPathDist");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

}  // namespace uking::ai
