#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmBlownOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmBlownOff, ksys::act::ai::Action)
public:
    explicit AnmBlownOff(const InitArg& arg);
    ~AnmBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mOnGroundTime_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mBlownHeight_s{};
    // static_param at offset 0x38
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x40
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x48
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x50
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x58
    const bool* mIsFinishByAnm_s{};
    // static_param at offset 0x60
    const bool* mIsWaitForAnmEnd_s{};
    // static_param at offset 0x68
    const bool* mIsItemDrop_s{};
    // static_param at offset 0x70
    const bool* mIsFinishByWater_s{};
    // static_param at offset 0x78
    const bool* mUseKnockbackDir_s{};
    // static_param at offset 0x80
    sead::SafeString mAS_s{};
};

}  // namespace uking::action
