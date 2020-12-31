#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormRoam, ksys::act::ai::Ai)
public:
    explicit SandwormRoam(const InitArg& arg);
    ~SandwormRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mJumpTimerBase_s{};
    // static_param at offset 0x40
    const float* mJumpTimerRand_s{};
    // static_param at offset 0x48
    const float* mJumpDistanceXZ_s{};
};

}  // namespace uking::ai
