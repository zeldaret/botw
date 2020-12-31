#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChangeWeatherTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChangeWeatherTagRoot, ksys::act::ai::Ai)
public:
    explicit ChangeWeatherTagRoot(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mWeather_m{};
    // map_unit_param at offset 0x40
    const int* mWeatherEff_m{};
    // map_unit_param at offset 0x48
    const int* mPaletteSel_m{};
    // map_unit_param at offset 0x50
    const int* mPSelSpeed_m{};
    // map_unit_param at offset 0x58
    const int* mIgnitedLevel_m{};
    // map_unit_param at offset 0x60
    const float* mTemperatureDay_m{};
    // map_unit_param at offset 0x68
    const float* mTemperatureNight_m{};
    // map_unit_param at offset 0x70
    const float* mTemperatureDirectDay_m{};
    // map_unit_param at offset 0x78
    const float* mTemperatureDirectNight_m{};
    // map_unit_param at offset 0x80
    const bool* mCloudShadowOff_m{};
    // map_unit_param at offset 0x88
    const bool* mBluffThunderOff_m{};
    // map_unit_param at offset 0x90
    const bool* mFogMinusCorrection_m{};
};

}  // namespace uking::ai
