#pragma once

#include "Game/AI/Action/actionOneTimeWaterFloatStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatIgniteToTarget : public OneTimeWaterFloatStopASPlay {
    SEAD_RTTI_OVERRIDE(WaterFloatIgniteToTarget, OneTimeWaterFloatStopASPlay)
public:
    explicit WaterFloatIgniteToTarget(const InitArg& arg);
    ~WaterFloatIgniteToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const float* mIgniteSpeed_s{};
    // static_param at offset 0x90
    const float* mMaxNoiseDist_s{};
    // static_param at offset 0x98
    const float* mOffsetHeight_s{};
    // static_param at offset 0xa0
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mIgniteOffset_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mIgniteRotSpeed_s{};
    // static_param at offset 0xc8
    const sead::Vector3f* mDirMinAngle_s{};
    // static_param at offset 0xd0
    const sead::Vector3f* mDirMaxAngle_s{};
    // dynamic_param at offset 0xd8
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xe0
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
};

}  // namespace uking::action
