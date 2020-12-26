#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Ragdoll : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Ragdoll, ksys::act::ai::Action)
public:
    explicit Ragdoll(const InitArg& arg);
    ~Ragdoll() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const int* mInWaterDownTime_s{};
    // static_param at offset 0x30
    const int* mForceFinishTime_s{};
    // static_param at offset 0x38
    const int* mOnGroundDownTime_s{};
    // static_param at offset 0x40
    const int* mStartUpdateFriction_s{};
    // static_param at offset 0x48
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x50
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x58
    const float* mGetUpGroundAngle_s{};
    // static_param at offset 0x60
    const float* mForceEndWaterDepth_s{};
    // static_param at offset 0x68
    const bool* mIsWaitAS_s{};
    // static_param at offset 0x70
    const bool* mIsItemDrop_s{};
    // static_param at offset 0x78
    const bool* mIsCheckVibrate_s{};
    // static_param at offset 0x80
    sead::SafeString mASName_s{};
    // static_param at offset 0x90
    sead::SafeString mPosBaseRagdollRbName_s{};
    // static_param at offset 0xa0
    sead::SafeString mStableASName_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mDownBackCtrlOffset_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mDownFrontCtrlOffset_s{};
    // aitree_variable at offset 0x110
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
