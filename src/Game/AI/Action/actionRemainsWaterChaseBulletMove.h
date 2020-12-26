#pragma once

#include "Game/AI/Action/actionRemainsWaterBulletAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterChaseBulletMove : public RemainsWaterBulletAction {
    SEAD_RTTI_OVERRIDE(RemainsWaterChaseBulletMove, RemainsWaterBulletAction)
public:
    explicit RemainsWaterChaseBulletMove(const InitArg& arg);
    ~RemainsWaterChaseBulletMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const float* mBaseChaseSpd_s{};
    // static_param at offset 0x88
    const float* mMaxChaseSpd_s{};
    // static_param at offset 0x90
    const float* mChaseSpdRate_s{};
    // static_param at offset 0x98
    const float* mChaseAngleRate_s{};
    // static_param at offset 0xa0
    const float* mDepthOffset_s{};
    // static_param at offset 0xa8
    const float* mMaxPredictFrame_s{};
    // static_param at offset 0xb0
    const float* mMinPredictFrame_s{};
    // static_param at offset 0xb8
    const float* mStartPredictDist_s{};
    // static_param at offset 0xc0
    const float* mEndPredictDist_s{};
    // static_param at offset 0xc8
    const float* mWeakChaseTimer_s{};
    // static_param at offset 0xd0
    const sead::Vector3f* mBaseTargetOffset_s{};
    // static_param at offset 0xd8
    const sead::Vector3f* mBaseTargetRandOffset_s{};
    // map_unit_param at offset 0xe0
    const float* mRemainsWaterBulletAngle_m{};
    // map_unit_param at offset 0xe8
    const sead::Vector3f* mRemainsWaterBulletOffset_m{};
};

}  // namespace uking::action
