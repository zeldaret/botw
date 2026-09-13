#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MultiVacuumRotScaleTimeByDistWithTgtBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MultiVacuumRotScaleTimeByDistWithTgtBase, ksys::act::ai::Action)
public:
    explicit MultiVacuumRotScaleTimeByDistWithTgtBase(const InitArg& arg);
    ~MultiVacuumRotScaleTimeByDistWithTgtBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const int* mAddTimeVacuuming_s{};
    // static_param at offset 0x30
    const int* mAddTimeNearVacuuming_s{};
    // static_param at offset 0x38
    const int* mVacuumNum_s{};
    // static_param at offset 0x40
    const int* mChangeableTiming_s{};
    // static_param at offset 0x48
    const float* mEndDist_s{};
    // static_param at offset 0x50
    const float* mMaxDist_s{};
    // static_param at offset 0x58
    const float* mTargetAccRate_s{};
    // static_param at offset 0x60
    const float* mTargetSpeed_s{};
    // static_param at offset 0x68
    const float* mBaseWeight_s{};
    // static_param at offset 0x70
    const float* mVacuumAngle_s{};
    // static_param at offset 0x78
    const float* mNearDist_s{};
    // static_param at offset 0x80
    sead::SafeString mStartAS_s{};
    // static_param at offset 0x90
    sead::SafeString mLoopAS_s{};
    // static_param at offset 0xa0
    sead::SafeString mEndAS_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mVacuumPosOffset_s{};
};

}  // namespace uking::action
