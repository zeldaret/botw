#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormFindTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormFindTarget, ksys::act::ai::Ai)
public:
    explicit SandwormFindTarget(const InitArg& arg);
    ~SandwormFindTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const float* mLostVMin_s{};
    // static_param at offset 0x48
    const float* mLostVMax_s{};
    // static_param at offset 0x50
    const float* mLostRange_s{};
    // static_param at offset 0x58
    const float* mAttackRange_s{};
};

}  // namespace uking::ai
