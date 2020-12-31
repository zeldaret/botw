#include "Game/AI/AI/aiPriestBossActorGiantRoot.h"

namespace uking::ai {

PriestBossActorGiantRoot::PriestBossActorGiantRoot(const InitArg& arg) : PriestBossActorRoot(arg) {}

PriestBossActorGiantRoot::~PriestBossActorGiantRoot() = default;

bool PriestBossActorGiantRoot::init_(sead::Heap* heap) {
    return PriestBossActorRoot::init_(heap);
}

void PriestBossActorGiantRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorRoot::enter_(params);
}

void PriestBossActorGiantRoot::leave_() {
    PriestBossActorRoot::leave_();
}

void PriestBossActorGiantRoot::loadParams_() {
    PriestBossActorRoot::loadParams_();
    getStaticParam(&mFreqIronBallAttack_s, "FreqIronBallAttack");
    getStaticParam(&mFreqBigEarthReleaseAttack_s, "FreqBigEarthReleaseAttack");
    getStaticParam(&mFreqEyeBeamAttack_s, "FreqEyeBeamAttack");
    getStaticParam(&mFreqStageRotation_s, "FreqStageRotation");
    getStaticParam(&mFloatDistFromPlayer_s, "FloatDistFromPlayer");
    getStaticParam(&mIsFreeMoving_s, "IsFreeMoving");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsActive_a, "IsActive");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

}  // namespace uking::ai
