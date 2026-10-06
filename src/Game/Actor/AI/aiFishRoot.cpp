#include "Game/Actor/AI/aiFishRoot.h"

namespace uking::ai {

FishRoot::FishRoot(const InitArg& arg) : CapturedActorRoot(arg) {}

FishRoot::~FishRoot() = default;

bool FishRoot::init_(sead::Heap* heap) {
    return CapturedActorRoot::init_(heap);
}

void FishRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    CapturedActorRoot::enter_(params);
}

void FishRoot::leave_() {
    CapturedActorRoot::leave_();
}

void FishRoot::loadParams_() {
    CapturedActorRoot::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOnGroundDepth_s, "OnGroundDepth");
    getStaticParam(&mNextJumpTimeBase_s, "NextJumpTimeBase");
    getStaticParam(&mNextJumpTimeRand_s, "NextJumpTimeRand");
    getStaticParam(&mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getStaticParam(&mFrameUntilOutOfWater_s, "FrameUntilOutOfWater");
    getStaticParam(&mDistRunFromPlayerOnReturn_s, "DistRunFromPlayerOnReturn");
    getStaticParam(&mIgnoreFoodBase_s, "IgnoreFoodBase");
    getStaticParam(&mIgnoreFoodRand_s, "IgnoreFoodRand");
    getStaticParam(&mIgnoreFoodAfterSuccessBase_s, "IgnoreFoodAfterSuccessBase");
    getStaticParam(&mIgnoreFoodAfterSuccessRand_s, "IgnoreFoodAfterSuccessRand");
}

}  // namespace uking::ai
