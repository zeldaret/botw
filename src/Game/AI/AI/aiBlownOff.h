#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BlownOff, ksys::act::ai::Ai)
public:
    explicit BlownOff(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDrownDepth_s{};
    // static_param at offset 0x40
    const bool* mIsForceGetUp_s{};
    // static_param at offset 0x48
    const bool* mIsIceBreak_s{};
};

}  // namespace uking::ai
