#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CircleMoveInFluid : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CircleMoveInFluid, ksys::act::ai::Ai)
public:
    explicit CircleMoveInFluid(const InitArg& arg);
    ~CircleMoveInFluid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mRadiusX_s{};
    // static_param at offset 0x48
    const float* mRadiusZ_s{};
    // static_param at offset 0x50
    const float* mMinRandRadiusRate_s{};
    // static_param at offset 0x58
    const float* mMaxRandRadiusRate_s{};
    // static_param at offset 0x60
    const float* mAddAngleRateX_s{};
    // static_param at offset 0x68
    const float* mAddAngleRateZ_s{};
    // static_param at offset 0x70
    const float* mRandRangeY_s{};
    // static_param at offset 0x78
    const float* mRandRangeYOffest_s{};
    // static_param at offset 0x80
    const float* mLimitSpeedMoveY_s{};
    // static_param at offset 0x88
    const float* mChangeInterval_s{};
    // static_param at offset 0x90
    const float* mRandChangeInterval_s{};
    // static_param at offset 0x98
    const float* mReverseMoveRate_s{};
    // static_param at offset 0xa0
    const bool* mIsSetSystemDeleteDistance_s{};
};

}  // namespace uking::ai
