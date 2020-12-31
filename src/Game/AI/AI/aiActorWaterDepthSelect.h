#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ActorWaterDepthSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ActorWaterDepthSelect, ksys::act::ai::Ai)
public:
    explicit ActorWaterDepthSelect(const InitArg& arg);
    ~ActorWaterDepthSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDeepDepth_s{};
    // static_param at offset 0x40
    const bool* mOnEnterOnly_s{};
    // static_param at offset 0x48
    const bool* mForceDeepChange_s{};
};

}  // namespace uking::ai
