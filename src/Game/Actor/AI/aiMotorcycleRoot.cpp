#include "Game/Actor/AI/aiMotorcycleRoot.h"

namespace uking::ai {

MotorcycleRoot::MotorcycleRoot(const InitArg& arg) : HorseRiddenStatusSelector(arg) {}

MotorcycleRoot::~MotorcycleRoot() = default;

bool MotorcycleRoot::init_(sead::Heap* heap) {
    return HorseRiddenStatusSelector::init_(heap);
}

void MotorcycleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRiddenStatusSelector::enter_(params);
}

void MotorcycleRoot::leave_() {
    HorseRiddenStatusSelector::leave_();
}

void MotorcycleRoot::loadParams_() {
    HorseRiddenStatusSelector::loadParams_();
    getStaticParam(&mInWaterRateForDisappear_s, "InWaterRateForDisappear");
    getStaticParam(&mDistanceToPlayerForDisappear_s, "DistanceToPlayerForDisappear");
    getStaticParam(&mNoiseEnergyEmpty_s, "NoiseEnergyEmpty");
    getStaticParam(&mNoiseNotRidden_s, "NoiseNotRidden");
    getStaticParam(&mNoiseThrottleClose_s, "NoiseThrottleClose");
    getStaticParam(&mNoiseThrottleOpen_s, "NoiseThrottleOpen");
    getStaticParam(&mForestFogRatioForDisappear_s, "ForestFogRatioForDisappear");
}

}  // namespace uking::ai
