#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BackStepAndAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BackStepAndAttack, ksys::act::ai::Ai)
public:
    explicit BackStepAndAttack(const InitArg& arg);
    ~BackStepAndAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mBackStepMax_s{};
    // static_param at offset 0x40
    const int* mTurnRepeatMax_s{};
    // static_param at offset 0x48
    const float* mBackStepMinDist_s{};
    // static_param at offset 0x50
    const float* mBackStepDist_s{};
    // static_param at offset 0x58
    const float* mFrontAngle_s{};
    // static_param at offset 0x60
    const float* mNoBackStepRange_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
