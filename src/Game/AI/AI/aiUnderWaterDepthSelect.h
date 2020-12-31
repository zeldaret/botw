#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnderWaterDepthSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(UnderWaterDepthSelect, ksys::act::ai::Ai)
public:
    explicit UnderWaterDepthSelect(const InitArg& arg);
    ~UnderWaterDepthSelect() override;

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
