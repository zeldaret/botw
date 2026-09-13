#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RideHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RideHorse, ksys::act::ai::Action)
public:
    explicit RideHorse(const InitArg& arg);
    ~RideHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mJumpHeightOffset_s{};
    // static_param at offset 0x28
    const float* mMaxSpeed_s{};
    // static_param at offset 0x30
    const float* mFarRotSpeed_s{};
    // static_param at offset 0x38
    const float* mNearRotSpeed_s{};
    // static_param at offset 0x40
    const float* mRideRotSpeed_s{};
    // static_param at offset 0x48
    const float* mLoopASInterpolateTime_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mPredictedRidePosOffset_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mPreRideSklRootOffset_s{};
    // dynamic_param at offset 0x60
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
