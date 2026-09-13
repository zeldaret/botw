#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TemperatureRandSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TemperatureRandSelect, ksys::act::ai::Ai)
public:
    explicit TemperatureRandSelect(const InitArg& arg);
    ~TemperatureRandSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mBaseChangeRatio_s{};
    // static_param at offset 0x40
    const int* museBaseRatioTiming_s{};
    // static_param at offset 0x48
    const float* mTemperatureChangeRatio_s{};
    // static_param at offset 0x50
    const float* mBaseTemperature_s{};
};

}  // namespace uking::ai
