#pragma once

#include "Game/AI/AI/aiSimpleWildlifeRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FishRoot : public SimpleWildlifeRoot {
    SEAD_RTTI_OVERRIDE(FishRoot, SimpleWildlifeRoot)
public:
    explicit FishRoot(const InitArg& arg);
    ~FishRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xf8
    const float* mInWaterDepth_s{};
    // static_param at offset 0x100
    const float* mOnGroundDepth_s{};
    // static_param at offset 0x108
    const float* mNextJumpTimeBase_s{};
    // static_param at offset 0x110
    const float* mNextJumpTimeRand_s{};
    // static_param at offset 0x118
    const float* mAllowReturnThreatDist_s{};
    // static_param at offset 0x120
    const float* mFrameUntilOutOfWater_s{};
    // static_param at offset 0x128
    const float* mDistRunFromPlayerOnReturn_s{};
    // static_param at offset 0x130
    const float* mIgnoreFoodBase_s{};
    // static_param at offset 0x138
    const float* mIgnoreFoodRand_s{};
    // static_param at offset 0x140
    const float* mIgnoreFoodAfterSuccessBase_s{};
    // static_param at offset 0x148
    const float* mIgnoreFoodAfterSuccessRand_s{};
};

}  // namespace uking::ai
