#pragma once

#include "Game/AI/AI/aiMotorcycleRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MotorcycleRoot : public MotorcycleRootBase {
    SEAD_RTTI_OVERRIDE(MotorcycleRoot, MotorcycleRootBase)
public:
    explicit MotorcycleRoot(const InitArg& arg);
    ~MotorcycleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mInWaterRateForDisappear_s{};
    // static_param at offset 0x40
    const float* mDistanceToPlayerForDisappear_s{};
    // static_param at offset 0x48
    const float* mNoiseEnergyEmpty_s{};
    // static_param at offset 0x50
    const float* mNoiseNotRidden_s{};
    // static_param at offset 0x58
    const float* mNoiseThrottleClose_s{};
    // static_param at offset 0x60
    const float* mNoiseThrottleOpen_s{};
    // static_param at offset 0x68
    const float* mForestFogRatioForDisappear_s{};
};

}  // namespace uking::ai
