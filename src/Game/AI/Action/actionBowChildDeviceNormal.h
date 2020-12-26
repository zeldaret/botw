#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildDeviceNormal : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildDeviceNormal, ksys::act::ai::Action)
public:
    explicit BowChildDeviceNormal(const InitArg& arg);
    ~BowChildDeviceNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mWaitTime_s{};
    // static_param at offset 0x30
    const float* mAccelRate_s{};
    // static_param at offset 0x38
    const float* mBrakeStartDist_s{};
    // static_param at offset 0x40
    const float* mVibrationSpeed_s{};
    // static_param at offset 0x48
    const float* mStopDist_s{};
    // static_param at offset 0x50
    const float* mVibrationLength_s{};
    // static_param at offset 0x58
    const float* mMoveTime_s{};
    // static_param at offset 0x60
    const bool* mIsMoveAccel_s{};
    // dynamic_param at offset 0x68
    int* mID_d{};
    // dynamic_param at offset 0x70
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x80
    ksys::act::BaseProcLink* mParentActor_d{};
};

}  // namespace uking::action
