#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeEnvForEnduranceDungeon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangeEnvForEnduranceDungeon, ksys::act::ai::Action)
public:
    explicit ChangeEnvForEnduranceDungeon(const InitArg& arg);
    ~ChangeEnvForEnduranceDungeon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mWeather_m{};
    // map_unit_param at offset 0x28
    const int* mIgnitedLevel_m{};
    // map_unit_param at offset 0x30
    const int* mWeatherEff_m{};
    // map_unit_param at offset 0x38
    const int* mPaletteSel_m{};
    // map_unit_param at offset 0x40
    const int* mTimeForSkyEnv_m{};
    // map_unit_param at offset 0x48
    const float* mTemperatureDirectDay_m{};
    // map_unit_param at offset 0x50
    const float* mTemperatureDirectNight_m{};
};

}  // namespace uking::action
