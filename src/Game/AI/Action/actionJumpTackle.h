#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpTackle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpTackle, ksys::act::ai::Action)
public:
    explicit JumpTackle(const InitArg& arg);
    ~JumpTackle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mMinSpeed_s{};
    // static_param at offset 0x30
    const float* mJumpHeight_s{};
    // static_param at offset 0x38
    const float* mJumpHeightMaxOffset_s{};
    // static_param at offset 0x40
    const bool* mIsFinishedAtPreLandFrame_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
