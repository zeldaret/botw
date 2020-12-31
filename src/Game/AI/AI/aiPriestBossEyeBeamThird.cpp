#include "Game/AI/AI/aiPriestBossEyeBeamThird.h"

namespace uking::ai {

PriestBossEyeBeamThird::PriestBossEyeBeamThird(const InitArg& arg) : PriestBossEyeBeam(arg) {}

PriestBossEyeBeamThird::~PriestBossEyeBeamThird() = default;

bool PriestBossEyeBeamThird::init_(sead::Heap* heap) {
    return PriestBossEyeBeam::init_(heap);
}

void PriestBossEyeBeamThird::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossEyeBeam::enter_(params);
}

void PriestBossEyeBeamThird::leave_() {
    PriestBossEyeBeam::leave_();
}

void PriestBossEyeBeamThird::loadParams_() {
    PriestBossEyeBeam::loadParams_();
    getAITreeVariable(&mIsArrivedAtDestination_a, "IsArrivedAtDestination");
    getAITreeVariable(&mDestinationPos_a, "DestinationPos");
    getAITreeVariable(&mFacePos_a, "FacePos");
}

}  // namespace uking::ai
