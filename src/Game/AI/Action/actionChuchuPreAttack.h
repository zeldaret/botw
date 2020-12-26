#pragma once

#include "Game/AI/Action/actionChuchuPreAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChuchuPreAttack : public ChuchuPreAttackBase {
    SEAD_RTTI_OVERRIDE(ChuchuPreAttack, ChuchuPreAttackBase)
public:
    explicit ChuchuPreAttack(const InitArg& arg);
    ~ChuchuPreAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mSubASSlot_s{};
    // static_param at offset 0xc8
    const float* mHitImpactForceSmallSwordS_s{};
    // static_param at offset 0xd0
    const float* mHitImpactForceSmallSwordL_s{};
    // static_param at offset 0xd8
    const float* mHitImpactForceLargeSwordS_s{};
    // static_param at offset 0xe0
    const float* mHitImpactForceLargeSwordL_s{};
    // static_param at offset 0xe8
    const float* mHitImpactForceSpearS_s{};
    // static_param at offset 0xf0
    const float* mHitImpactForceSpearL_s{};
    // static_param at offset 0xf8
    const float* mPosReduceRatioByDamage_s{};
    // static_param at offset 0x100
    sead::SafeString mDamageAS_s{};
    // static_param at offset 0x110
    sead::SafeString mSubAS_s{};
    // static_param at offset 0x120
    sead::SafeString mLeaveSubAS_s{};
    // static_param at offset 0x130
    sead::SafeString mDamageSubAS_s{};
};

}  // namespace uking::action
