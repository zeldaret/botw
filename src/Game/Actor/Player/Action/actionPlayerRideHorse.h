#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerRideHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerRideHorse, ksys::act::ai::Action)
public:
    explicit PlayerRideHorse(const InitArg& arg);
    ~PlayerRideHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAccelerateInputDelayGear0_s{};
    // static_param at offset 0x28
    const int* mAccelerateInputDelayGear1_s{};
    // static_param at offset 0x30
    const int* mAccelerateInputDelayGear2_s{};
    // static_param at offset 0x38
    const int* mAccelerateInputDelayGear3_s{};
    // static_param at offset 0x40
    const int* mAccelerateInputDelayGearTop_s{};
    // static_param at offset 0x48
    const int* mAccInputIgnoreFramesGear0_s{};
    // static_param at offset 0x50
    const int* mAccInputIgnoreFramesGear1_s{};
    // static_param at offset 0x58
    const int* mAccInputIgnoreFramesGear2_s{};
    // static_param at offset 0x60
    const int* mAccInputIgnoreFramesGear3_s{};
    // static_param at offset 0x68
    const int* mAccInputIgnoreFramesGearTop_s{};
    // static_param at offset 0x70
    const float* mDecelerateInputThreshold_s{};
    // static_param at offset 0x78
    const float* mStopInputFrames_s{};
    // static_param at offset 0x80
    const float* mAccelerateInputThreshold_s{};
    // static_param at offset 0x88
    const float* mMoveBackInputThreshold_s{};
    // static_param at offset 0x90
    const float* mStickXClampAtGear0_s{};
    // static_param at offset 0x98
    const float* mTurnStickXInputThreshold_s{};
    // static_param at offset 0xa0
    const float* mConstraintBreakThreshold_s{};
    // dynamic_param at offset 0xa8
    bool* mHasToPlayRidingOnAS_d{};
};

}  // namespace uking::action
