#include "Game/AI/AI/aiEnemyNormal.h"

namespace uking::ai {

EnemyNormal::EnemyNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNormal::~EnemyNormal() = default;

bool EnemyNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNormal::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSoundLostTimer_s, "SoundLostTimer");
    getStaticParam(&mNoActionReactTimeMin_s, "NoActionReactTimeMin");
    getStaticParam(&mNoActionReactTimeMax_s, "NoActionReactTimeMax");
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mNpcTerritoryArea_s, "NpcTerritoryArea");
    getStaticParam(&mNoPlayerTerritoryArea_s, "NoPlayerTerritoryArea");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mEnlargeAwnRatio_s, "EnlargeAwnRatio");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mSpeadDist2_s, "SpeadDist2");
    getStaticParam(&mHomePosRadius_s, "HomePosRadius");
    getStaticParam(&mSubsTerritoryArea_s, "SubsTerritoryArea");
    getStaticParam(&mLostExtinguishFireDist_s, "LostExtinguishFireDist");
    getStaticParam(&mShortRangeTerritoryArea_s, "ShortRangeTerritoryArea");
    getStaticParam(&mCloseRangeTerritoryArea_s, "CloseRangeTerritoryArea");
    getStaticParam(&mPressBreakObject_s, "PressBreakObject");
    getStaticParam(&mTerritoryHeight_s, "TerritoryHeight");
    getStaticParam(&mIsMindDoubtTarget_s, "IsMindDoubtTarget");
    getStaticParam(&mFortressTag_s, "FortressTag");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getAITreeVariable(&mPlayerSoundSealRefCount_a, "PlayerSoundSealRefCount");
    getAITreeVariable(&mSealNoPlayerAwnRequestCount_a, "SealNoPlayerAwnRequestCount");
}

}  // namespace uking::ai
