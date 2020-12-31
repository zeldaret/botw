#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SunazarashiRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(SunazarashiRoot, PreyRoot)
public:
    explicit SunazarashiRoot(const InitArg& arg);
    ~SunazarashiRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x208
    const float* mStunNoiseLevel_s{};
    // static_param at offset 0x210
    const float* mClashSpeed_s{};
    // static_param at offset 0x218
    const float* mClashAngle_s{};
    // static_param at offset 0x220
    const bool* mEnableHangAlways_s{};
    // map_unit_param at offset 0x228
    const bool* mForbidSystemDeleteDistance_m{};
    // aitree_variable at offset 0x230
    sead::Vector3f* mSunazarashiReturnPos_a{};
};

}  // namespace uking::ai
