#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeatherReactionCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeatherReactionCheck, ksys::act::ai::Ai)
public:
    explicit WeatherReactionCheck(const InitArg& arg);
    ~WeatherReactionCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRandTime_s{};
    // static_param at offset 0x40
    const bool* mIsReactionRain_s{};
    // static_param at offset 0x48
    const bool* mIsReactionSnow_s{};
    // static_param at offset 0x50
    const bool* mIsReturnNormal_s{};
    // static_param at offset 0x58
    const bool* mIsForceChangeable_s{};
};

}  // namespace uking::ai
