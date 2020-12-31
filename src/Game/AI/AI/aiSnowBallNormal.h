#pragma once

#include "Game/AI/AI/aiFixableLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SnowBallNormal : public FixableLiftable {
    SEAD_RTTI_OVERRIDE(SnowBallNormal, FixableLiftable)
public:
    explicit SnowBallNormal(const InitArg& arg);
    ~SnowBallNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mScaleRate_s{};
    // static_param at offset 0xe8
    const float* mScaleMax_s{};
    // static_param at offset 0xf0
    const float* mCarryScaleLimit_s{};
    // static_param at offset 0xf8
    const float* mSendSignalLinearVelTh_s{};
    // static_param at offset 0x100
    const float* mSendSignalScaleTh_s{};
    // static_param at offset 0x108
    const float* mScaleMin_s{};
    // static_param at offset 0x110
    const float* mDeleteUnderWaterDepth_s{};
    // static_param at offset 0x118
    const float* mMaxImpulseMassRate_s{};
    // static_param at offset 0x120
    const float* mAttReturnOnOffset_s{};
    // static_param at offset 0x128
    const float* mScaleIncreaseDistance_s{};
    // static_param at offset 0x130
    const float* mItemDropSetScaleOffset_s{};
    // static_param at offset 0x138
    const float* mItemDropDeleteScaleOffset_s{};
    // static_param at offset 0x140
    const float* mMinImpulseRatio_s{};
};

}  // namespace uking::ai
