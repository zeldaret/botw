#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WillBallAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WillBallAction, ksys::act::ai::Action)
public:
    explicit WillBallAction(const InitArg& arg);
    ~WillBallAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpeed_s{};
    // static_param at offset 0x30
    const float* mReachRange_s{};
    // static_param at offset 0x38
    const float* mTiredAngle_s{};
    // static_param at offset 0x40
    const float* mRotBaseRatio_s{};
    // static_param at offset 0x48
    const float* mAccel_s{};
    // static_param at offset 0x50
    const bool* mIsIgnoreLastSpRot_s{};
    // static_param at offset 0x58
    const bool* mIsAddAABBHeight_s{};
    // static_param at offset 0x60
    const bool* mIsGround_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
