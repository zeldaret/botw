#include "Game/AI/AI/aiGiantEarthReleaseAttack.h"

namespace uking::ai {

GiantEarthReleaseAttack::GiantEarthReleaseAttack(const InitArg& arg) : EarthReleaseAttack(arg) {}

GiantEarthReleaseAttack::~GiantEarthReleaseAttack() = default;

bool GiantEarthReleaseAttack::init_(sead::Heap* heap) {
    return EarthReleaseAttack::init_(heap);
}

void GiantEarthReleaseAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    EarthReleaseAttack::enter_(params);
}

void GiantEarthReleaseAttack::leave_() {
    EarthReleaseAttack::leave_();
}

void GiantEarthReleaseAttack::loadParams_() {
    EarthReleaseAttack::loadParams_();
    getStaticParam(&mStartHeight_s, "StartHeight");
    getStaticParam(&mStartDistFromTarget_s, "StartDistFromTarget");
    getAITreeVariable(&mKeepDistFromGround_a, "KeepDistFromGround");
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
}

}  // namespace uking::ai
