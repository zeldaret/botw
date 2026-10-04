#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimTimingAttackMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimTimingAttackMove, ksys::act::ai::Action)
public:
    explicit AnimTimingAttackMove(const InitArg& arg);
    ~AnimTimingAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mJumpHeight_s{};
    // static_param at offset 0x28
    const float* mMaxSpeed_s{};
    // static_param at offset 0x30
    const bool* mIsRound_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // static_param at offset 0x48
    sead::SafeString mRigidBodyName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
