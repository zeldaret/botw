#include "Game/AI/AI/aiMotorcycleRoot.h"

namespace uking::ai {

MotorcycleRoot::MotorcycleRoot(const InitArg& arg) : MotorcycleRootBase(arg) {}

MotorcycleRoot::~MotorcycleRoot() = default;

bool MotorcycleRoot::init_(sead::Heap* heap) {
    return MotorcycleRootBase::init_(heap);
}

void MotorcycleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    MotorcycleRootBase::enter_(params);
}

void MotorcycleRoot::leave_() {
    MotorcycleRootBase::leave_();
}

void MotorcycleRoot::loadParams_() {
    MotorcycleRootBase::loadParams_();
    getStaticParam(&mInWaterRateForDisappear_s, "InWaterRateForDisappear");
    getStaticParam(&mDistanceToPlayerForDisappear_s, "DistanceToPlayerForDisappear");
    getStaticParam(&mNoiseEnergyEmpty_s, "NoiseEnergyEmpty");
    getStaticParam(&mNoiseNotRidden_s, "NoiseNotRidden");
    getStaticParam(&mNoiseThrottleClose_s, "NoiseThrottleClose");
    getStaticParam(&mNoiseThrottleOpen_s, "NoiseThrottleOpen");
    getStaticParam(&mForestFogRatioForDisappear_s, "ForestFogRatioForDisappear");
}

}  // namespace uking::ai
