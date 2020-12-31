#include "Game/AI/AI/aiLandHumEnemyUnarmedBattle.h"

namespace uking::ai {

LandHumEnemyUnarmedBattle::LandHumEnemyUnarmedBattle(const InitArg& arg)
    : UnarmedEnemySearch(arg) {}

LandHumEnemyUnarmedBattle::~LandHumEnemyUnarmedBattle() = default;

void LandHumEnemyUnarmedBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
}

void LandHumEnemyUnarmedBattle::leave_() {
    UnarmedEnemySearch::leave_();
}

void LandHumEnemyUnarmedBattle::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mSearchWeaponDist_s, "SearchWeaponDist");
    getStaticParam(&mSearchBaseWeaponDist_s, "SearchBaseWeaponDist");
    getStaticParam(&mSearchWeaponTargetDist_s, "SearchWeaponTargetDist");
    getStaticParam(&mSearchBowTargetDist_s, "SearchBowTargetDist");
    getStaticParam(&mGrabCheckRadius_s, "GrabCheckRadius");
    getStaticParam(&mSearchObjectDist_s, "SearchObjectDist");
    getStaticParam(&mItemChaseableSpd_s, "ItemChaseableSpd");
    getStaticParam(&mAttOffset_s, "AttOffset");
    getStaticParam(&mCanGrabHeavy_s, "CanGrabHeavy");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mExplosivesAvoidSpeed_s, "ExplosivesAvoidSpeed");
    getStaticParam(&mExplosivesAvoidAng_s, "ExplosivesAvoidAng");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mOnCoHitAllowGrabAngle_s, "OnCoHitAllowGrabAngle");
}

}  // namespace uking::ai
