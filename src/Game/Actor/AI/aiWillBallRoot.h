#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WillBallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WillBallRoot, ksys::act::ai::Ai)
public:
    explicit WillBallRoot(const InitArg& arg);
    ~WillBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMagneLightningTime_s{};
    // static_param at offset 0x40
    const int* mMinimizedTime_s{};
    // static_param at offset 0x48
    const float* mImmidiateLightningXZ_s{};
    // static_param at offset 0x50
    const float* mImmidiateLightningY_s{};
    // static_param at offset 0x58
    const float* mImmidiateLightningXZTarget_s{};
    // static_param at offset 0x60
    const float* mImmidiateLightningYTarget_s{};
    // static_param at offset 0x68
    const float* mLightningTimeMinimizeDist_s{};
    // static_param at offset 0x70
    const bool* mIsExplode_s{};
    // map_unit_param at offset 0x78
    const int* mCount_m{};
};

}  // namespace uking::ai
