#pragma once

#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackSwim : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(BackSwim, WaterFloatBase)
public:
    explicit BackSwim(const InitArg& arg);
    ~BackSwim() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const int* mTime_s{};
    // static_param at offset 0x68
    const int* mWeaponIdx_s{};
    // static_param at offset 0x70
    const float* mSpeed_s{};
    // static_param at offset 0x78
    const float* mRotSpd_s{};
    // static_param at offset 0x80
    const float* mRotAddRatio_s{};
    // static_param at offset 0x88
    const float* mFinishDist_s{};
    // static_param at offset 0x90
    const float* mDecelRatio_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0xa0
    const bool* mIsCheckCliff_s{};
};

}  // namespace uking::action
