#include "Game/AI/AI/aiSiteBossSpearAttackRoot.h"

namespace uking::ai {

SiteBossSpearAttackRoot::SiteBossSpearAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearAttackRoot::~SiteBossSpearAttackRoot() = default;

bool SiteBossSpearAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSpearAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSpearAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSpearAttackRoot::loadParams_() {
    getStaticParam(&mThrowSpearRate_s, "ThrowSpearRate");
    getStaticParam(&mBeamRate_s, "BeamRate");
    getStaticParam(&mIceBulletRate_s, "IceBulletRate");
    getStaticParam(&mSweepRateAtFar_s, "SweepRateAtFar");
    getStaticParam(&mSweepRateAtNear_s, "SweepRateAtNear");
    getStaticParam(&mReturnWaitCount_s, "ReturnWaitCount");
    getStaticParam(&mBeamPatternChangeHP_s, "BeamPatternChangeHP");
    getStaticParam(&mFarDistanceAttackRange_s, "FarDistanceAttackRange");
    getStaticParam(&mNearDistanceAttackRange_s, "NearDistanceAttackRange");
    getStaticParam(&mVerticalAttackRange_s, "VerticalAttackRange");
    getStaticParam(&mOnIceBlockHeight_s, "OnIceBlockHeight");
    getStaticParam(&mIsBowAimedCounterOn_s, "IsBowAimedCounterOn");
    getStaticParam(&mIsIceBulletOn_s, "IsIceBulletOn");
    getStaticParam(&mWarpAnchorFirstSuffix_s, "WarpAnchorFirstSuffix");
    getStaticParam(&mWarpAnchorAfterSuffix_s, "WarpAnchorAfterSuffix");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

}  // namespace uking::ai
