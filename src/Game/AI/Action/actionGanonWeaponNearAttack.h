#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonWeaponNearAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonWeaponNearAttack, ksys::act::ai::Action)
public:
    explicit GanonWeaponNearAttack(const InitArg& arg);
    ~GanonWeaponNearAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mAttackPower_s{};
    // static_param at offset 0x30
    const int* mAtkMinPower_s{};
    // static_param at offset 0x38
    const int* mAtAttr_s{};
    // static_param at offset 0x40
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x48
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x50
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x58
    const float* mAttackCancelDist_s{};
    // static_param at offset 0x60
    const float* mAttackCancelAng_s{};
    // static_param at offset 0x68
    const float* mBattleNodeOffsetLR_s{};
    // static_param at offset 0x70
    const float* mBattleNodeOffsetUD_s{};
    // static_param at offset 0x78
    const bool* mIsGuardPierce_s{};
    // static_param at offset 0x80
    const bool* mIsGuardBreak_s{};
    // static_param at offset 0x88
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
