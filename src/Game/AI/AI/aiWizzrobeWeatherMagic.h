#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeWeatherMagic : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeWeatherMagic, ksys::act::ai::Ai)
public:
    explicit WizzrobeWeatherMagic(const InitArg& arg);
    ~WizzrobeWeatherMagic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mWizzrobeMagicWeatherUnit_a{};
    // static_param at offset 0x40
    const float* mRiseLength_s{};
    // static_param at offset 0x48
    const float* mTimer_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
