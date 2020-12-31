#include "Game/AI/AI/aiPriestBossGiantStageRotRoot.h"

namespace uking::ai {

PriestBossGiantStageRotRoot::PriestBossGiantStageRotRoot(const InitArg& arg)
    : PriestBossMode(arg) {}

PriestBossGiantStageRotRoot::~PriestBossGiantStageRotRoot() = default;

bool PriestBossGiantStageRotRoot::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossGiantStageRotRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossGiantStageRotRoot::leave_() {
    PriestBossMode::leave_();
}

void PriestBossGiantStageRotRoot::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mCentralAngle_s, "CentralAngle");
    getStaticParam(&mPercentRadiusHeight_s, "PercentRadiusHeight");
    getStaticParam(&mIronBallHeightOffset_s, "IronBallHeightOffset");
    getStaticParam(&mArcPercent_s, "ArcPercent");
    getStaticParam(&mZOffset_s, "ZOffset");
    getStaticParam(&mZOffsetIndex_s, "ZOffsetIndex");
    getStaticParam(&mHoldBallsCounterLength_s, "HoldBallsCounterLength");
    getStaticParam(&mBallsReleaseIntervalFrames_s, "BallsReleaseIntervalFrames");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mFacePos_a, "FacePos");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
