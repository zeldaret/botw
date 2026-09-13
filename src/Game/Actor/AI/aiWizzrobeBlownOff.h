#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeBlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeBlownOff, ksys::act::ai::Ai)
public:
    explicit WizzrobeBlownOff(const InitArg& arg);
    ~WizzrobeBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDrownDepth_s{};
    // static_param at offset 0x40
    const bool* mIsForceGetUp_s{};
};

}  // namespace uking::ai
