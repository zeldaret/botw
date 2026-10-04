#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkWarp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkWarp, ksys::act::ai::Ai)
public:
    explicit WolfLinkWarp(const InitArg& arg);
    ~WolfLinkWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNumCalcPerFrame_s{};
    // static_param at offset 0x40
    const int* mFramesUntilFail_s{};
    // static_param at offset 0x48
    const float* mTransitFrames_s{};
    // static_param at offset 0x50
    const float* mWarpFromPlayerOffset_s{};
    // static_param at offset 0x58
    const float* mInitialAngle_s{};
    // static_param at offset 0x60
    const float* mAreaSearchRadius_s{};
    // static_param at offset 0x68
    const float* mAreaSearchCharacterRadius_s{};
    // static_param at offset 0x70
    const float* mAreaThreshold_s{};
    // dynamic_param at offset 0x78
    int* mWarpType_d{};
};

}  // namespace uking::ai
