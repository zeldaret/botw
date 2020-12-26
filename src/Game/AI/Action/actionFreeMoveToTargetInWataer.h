#pragma once

#include "Game/AI/Action/actionFreeMoveToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveToTargetInWataer : public FreeMoveToTarget {
    SEAD_RTTI_OVERRIDE(FreeMoveToTargetInWataer, FreeMoveToTarget)
public:
    explicit FreeMoveToTargetInWataer(const InitArg& arg);
    ~FreeMoveToTargetInWataer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    const float* mAllowMoveWaterDepth_s{};
    // static_param at offset 0xe0
    const float* mForceTurnLimitSpeedStream_s{};
    // static_param at offset 0xe8
    const bool* mIsForceTurnAgainstStream_s{};
    // static_param at offset 0xf0
    const bool* mForceUseFrontDir_s{};
};

}  // namespace uking::action
