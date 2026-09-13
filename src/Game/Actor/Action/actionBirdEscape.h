#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BirdEscape : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BirdEscape, ksys::act::ai::Action)
public:
    explicit BirdEscape(const InitArg& arg);
    ~BirdEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveSpeedMax_s{};
    // static_param at offset 0x28
    const float* mMoveSpeedMin_s{};
    // static_param at offset 0x30
    const float* mTurnSpeed_s{};
    // static_param at offset 0x38
    const float* mInterpolateFrameForMaxSpeed_s{};
    // static_param at offset 0x40
    const float* mTargetEscapeWidthMax_s{};
    // static_param at offset 0x48
    const float* mTargetEscapeWidthMin_s{};
    // static_param at offset 0x50
    const float* mTargetHeightMax_s{};
    // static_param at offset 0x58
    const float* mTargetHeightMin_s{};
    // static_param at offset 0x60
    const float* mTargetTurnAngle_s{};
    // static_param at offset 0x68
    const float* mContinueEscapeDistanceXZ_s{};
    // static_param at offset 0x70
    const float* mAdditionalWidth_s{};
    // static_param at offset 0x78
    const float* mTargetUpperAngle_s{};
    // static_param at offset 0x80
    const float* mStartReduceHeightRate_s{};
};

}  // namespace uking::action
