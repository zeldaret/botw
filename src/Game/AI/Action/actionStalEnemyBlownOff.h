#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StalEnemyBlownOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StalEnemyBlownOff, ksys::act::ai::Action)
public:
    explicit StalEnemyBlownOff(const InitArg& arg);
    ~StalEnemyBlownOff() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDownTimeBase_s{};
    // static_param at offset 0x28
    const int* mDownTimeRand_s{};
    // static_param at offset 0x30
    const float* mRecoverTimer_s{};
    // static_param at offset 0x38
    const float* mHeadShotSpeed_s{};
    // static_param at offset 0x40
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x48
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x50
    const float* mHeadSpeedRate_s{};
    // static_param at offset 0x58
    const float* mMinHeadSpeedY_s{};
    // static_param at offset 0x60
    const float* mMinHeadSpeedXZ_s{};
    // static_param at offset 0x68
    const bool* mHeadShotUseAddVec_s{};
    // static_param at offset 0x70
    sead::SafeString mPosBaseRagdollRbName_s{};
    // static_param at offset 0x80
    sead::SafeString mDisableBoneName_s{};
    // static_param at offset 0x90
    sead::SafeString mEnableConstraintName_s{};
    // static_param at offset 0xa0
    sead::SafeString mUseRagConName_s{};
    // static_param at offset 0xb0
    sead::SafeString mBlownOffASName_s{};
    // static_param at offset 0xc0
    sead::SafeString mPreUniteASName_s{};
    // static_param at offset 0xd0
    sead::SafeString mUniteASName_s{};
    // static_param at offset 0xe0
    sead::SafeString mDieASName_s{};
    // static_param at offset 0xf0
    sead::SafeString mHeadRagdollRigidNames_s{};
    // static_param at offset 0x100
    sead::SafeString mArmRagdollRigidNames_s{};
    // static_param at offset 0x110
    const sead::Vector3f* mDownBackCtrlOffset_s{};
    // static_param at offset 0x118
    const sead::Vector3f* mDownFrontCtrlOffset_s{};
    // static_param at offset 0x120
    const sead::Vector3f* mHeadShotAddVec_s{};
    // static_param at offset 0x128
    const sead::Vector3f* mHeadRotateOffset_s{};
};

}  // namespace uking::action
