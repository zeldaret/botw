#pragma once

#include "Game/AI/Action/actionJumpTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpToTargetFromWater : public JumpTo {
    SEAD_RTTI_OVERRIDE(JumpToTargetFromWater, JumpTo)
public:
    explicit JumpToTargetFromWater(const InitArg& arg);
    ~JumpToTargetFromWater() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa0
    const float* mFloatCycleTime_s{};
    // static_param at offset 0xa8
    const float* mFloatDepth_s{};
    // static_param at offset 0xb0
    const float* mFloatRadius_s{};
    // static_param at offset 0xb8
    sead::SafeString mPreJumpAS_s{};
    // static_param at offset 0xc8
    sead::SafeString mJumpAS_s{};
    // static_param at offset 0xd8
    sead::SafeString mLandAS_s{};
};

}  // namespace uking::action
