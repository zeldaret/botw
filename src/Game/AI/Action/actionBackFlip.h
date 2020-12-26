#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackFlip : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(BackFlip, RotateTurnToTarget)
public:
    explicit BackFlip(const InitArg& arg);
    ~BackFlip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x78
    void* mRefPosVibrateChecker_a{};
    // static_param at offset 0x80
    const float* mSpeed_s{};
    // static_param at offset 0x88
    const float* mPosRestRatio_s{};
    // static_param at offset 0x90
    const float* mJumpHeight_s{};
    // static_param at offset 0x98
    const float* mNearGrHeight_s{};
};

}  // namespace uking::action
