#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpMove, ksys::act::ai::Action)
public:
    explicit JumpMove(const InitArg& arg);
    ~JumpMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPreJumpWait_s{};
    // static_param at offset 0x28
    const float* mMaxMoveSpeed_s{};
    // static_param at offset 0x30
    const float* mMinMoveSpeed_s{};
    // static_param at offset 0x38
    const float* mRandAngleLimit_s{};
    // static_param at offset 0x40
    const float* mJumpHeight_s{};
    // static_param at offset 0x48
    sead::SafeString mASKey_s{};
};

}  // namespace uking::action
