#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InWaterSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InWaterSelect, ksys::act::ai::Ai)
public:
    explicit InWaterSelect(const InitArg& arg);
    ~InWaterSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mInWaterDepth_s{};
    // static_param at offset 0x40
    const float* mOutWaterDepth_s{};
    // static_param at offset 0x48
    const bool* mIsCheckEveryFrame_s{};
    // static_param at offset 0x50
    const bool* mIsForceChange_s{};
};

}  // namespace uking::ai
