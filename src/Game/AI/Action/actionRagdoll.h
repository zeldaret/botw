#pragma once

#include <math/seadVector.h>
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
    // ragdoll internal state at offset 0xc0
    sead::Vector3f mRagdollForce{};
    // ragdoll state at offset 0xcc
    s32 mCounter1{};
    s32 mCounter2{};
    // ragdoll state at offset 0xd4
    f32 mFloat1_d4{};
    // ragdoll state at offset 0xd8
    s32 mCounter3{};
    s32 mCounter4{};
    // ragdoll state at offset 0xe0
    f32 mFloat2_e0{};
    // ragdoll state at offset 0xe4
    s32 mCounter5{};
    s32 mCounter6{};
    // ragdoll state at offset 0xec: checked by BlownOff::isChangeable()
    s32 mChangeableState{};
    // ragdoll state at offset 0xf0
    f32 mFloat3_f0{};
    f32 mFloat4_f4{};
    // ragdoll state at offset 0xf8
    void* mStatePtr_f8{};
    // ragdoll state at offset 0x100
    s32 mCounter7_100{};
    // ragdoll state at offset 0x104
    bool mFlag_104{};
    // ragdoll state at offset 0x108
    void* mStatePtr2_108{};
    // aitree_variable at offset 0x110
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
