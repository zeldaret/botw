#include "Game/AI/AI/aiUnarmedEnemyNoiseTarget.h"

namespace uking::ai {

UnarmedEnemyNoiseTarget::UnarmedEnemyNoiseTarget(const InitArg& arg) : UnarmedEnemySearch(arg) {}

UnarmedEnemyNoiseTarget::~UnarmedEnemyNoiseTarget() = default;

void UnarmedEnemyNoiseTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
}

void UnarmedEnemyNoiseTarget::leave_() {
    UnarmedEnemySearch::leave_();
}

void UnarmedEnemyNoiseTarget::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mLostTime_s, "LostTime");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mSearchWeaponDist_s, "SearchWeaponDist");
    getStaticParam(&mSearchBaseWeaponDist_s, "SearchBaseWeaponDist");
    getStaticParam(&mAbsorpDist_s, "AbsorpDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchWeaponTargetDist_s, "SearchWeaponTargetDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
