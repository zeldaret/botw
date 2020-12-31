#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FishSafeReturn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FishSafeReturn, ksys::act::ai::Ai)
public:
    explicit FishSafeReturn(const InitArg& arg);
    ~FishSafeReturn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mInWaterDepth_s{};
    // static_param at offset 0x40
    const float* mDivePercent_s{};
    // static_param at offset 0x48
    const float* mAllowReturnThreatDist_s{};
    // dynamic_param at offset 0x50
    bool* mIsEscape_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
