#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BoomerangMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BoomerangMove, ksys::act::ai::Action)
public:
    explicit BoomerangMove(const InitArg& arg);
    ~BoomerangMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPreCurveTimer_s{};
    // static_param at offset 0x28
    const float* mRadSpeed_s{};
    // static_param at offset 0x30
    const float* mCurveSpeedRate_s{};
    // static_param at offset 0x38
    const float* mStraightSpeedRate_s{};
    // static_param at offset 0x40
    const float* mCurvePredictFrame_s{};
    // static_param at offset 0x48
    const float* mCurveCheckYDist_s{};
    // static_param at offset 0x50
    const float* mStraightPredictFrame_s{};
    // static_param at offset 0x58
    const float* mStraightCheckYDist_s{};
    // static_param at offset 0x60
    const float* mFlyLimitTime_s{};
    // static_param at offset 0x68
    sead::SafeString mCatchAttentionName_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mTargetOffset_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
