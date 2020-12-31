#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WithoutWeaponArrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WithoutWeaponArrow, ksys::act::ai::Ai)
public:
    explicit WithoutWeaponArrow(const InitArg& arg);
    ~WithoutWeaponArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAtAttr_s{};
    // static_param at offset 0x40
    const int* mStickTime_s{};
    // static_param at offset 0x48
    const float* mAccel_s{};
    // static_param at offset 0x50
    const float* mAimSpeed_s{};
    // static_param at offset 0x58
    const float* mFallAccel_s{};
    // static_param at offset 0x60
    const float* mFallAimSpeed_s{};
    // static_param at offset 0x68
    const float* mGravity_s{};
    // static_param at offset 0x70
    const float* mAtRange_s{};
    // static_param at offset 0x78
    const float* mAtImpulse_s{};
    // static_param at offset 0x80
    const float* mAtImpact_s{};
    // static_param at offset 0x88
    const float* mReflectDamageRate_s{};
    // static_param at offset 0x90
    const bool* mCanReflect_s{};
    // static_param at offset 0x98
    const bool* mIsReflectToParent_s{};
    // static_param at offset 0xa0
    const bool* mIsDelete_s{};
    // static_param at offset 0xa8
    const bool* mIsBreakIceBlock_s{};
    // static_param at offset 0xb0
    const bool* mIsAtHitPlayerIgnore_s{};
    // static_param at offset 0xb8
    const bool* mIsDeleteAtHit_s{};
    // static_param at offset 0xc0
    sead::SafeString mBindNodeName_s{};
    // static_param at offset 0xd0
    sead::SafeString mCallHitSEKey_s{};
    // static_param at offset 0xe0
    const sead::Vector3f* mReflectOffset_s{};
    // static_param at offset 0xe8
    const sead::Vector3f* mRotOffset_s{};
    // static_param at offset 0xf0
    const sead::Vector3f* mTransOffset_s{};
    // map_unit_param at offset 0xf8
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x100
    const int* mAttackPower_m{};
};

}  // namespace uking::ai
