#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildArrowRain : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildArrowRain, ksys::act::ai::Action)
public:
    explicit BowChildArrowRain(const InitArg& arg);
    ~BowChildArrowRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mRainMax_s{};
    // static_param at offset 0x28
    const float* mMoveSpeed_s{};
    // static_param at offset 0x30
    const float* mMoveHeight_s{};
    // static_param at offset 0x38
    const float* mWaitTime_s{};
    // static_param at offset 0x40
    const float* mMoveCountNum_s{};
    // static_param at offset 0x48
    const float* mMoveRange_s{};
    // static_param at offset 0x50
    const float* mMoveOffsetBase_s{};
    // static_param at offset 0x58
    const float* mRotateRate_s{};
    // static_param at offset 0x60
    const float* mRotateStepMax_s{};
    // static_param at offset 0x68
    const float* mAngleToTarget_s{};
    // static_param at offset 0x70
    const float* mTargetOffsetBase_s{};
    // static_param at offset 0x78
    const float* mRainScale_s{};
    // static_param at offset 0x80
    const float* mToTargetTime_s{};
    // dynamic_param at offset 0x88
    int* mID_d{};
    // dynamic_param at offset 0x90
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x98
    bool* mIsIgnoreHightOffset_d{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mMoveTargetPos_d{};
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcLink* mParentActor_d{};
};

}  // namespace uking::action
