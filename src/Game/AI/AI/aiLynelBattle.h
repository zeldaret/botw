#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelBattle, ksys::act::ai::Ai)
public:
    explicit LynelBattle(const InitArg& arg);
    ~LynelBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mCloseBattleRepeatMax_s{};
    // static_param at offset 0x48
    const int* mThroughAttackRepeatNum_s{};
    // static_param at offset 0x50
    const float* mCloseBattleStartDist_s{};
    // static_param at offset 0x58
    const float* mCloseBattleStartAngle_s{};
    // static_param at offset 0x60
    const float* mHornAttackRate_s{};
    // static_param at offset 0x68
    const float* mRoarRate_s{};
    // static_param at offset 0x70
    const float* mBreathStartLifeRate_s{};
    // static_param at offset 0x78
    const float* mRoarStartLifeRate_s{};
    // static_param at offset 0x80
    const float* mBattleEndDist_s{};
    // static_param at offset 0x88
    const float* mSkipBreathRoarRate_s{};
    // static_param at offset 0x90
    sead::SafeString mRoarFlamePartsKey_s{};
    // static_param at offset 0xa0
    sead::SafeString mBreathPartsKey0_s{};
    // static_param at offset 0xb0
    sead::SafeString mBreathPartsKey1_s{};
    // static_param at offset 0xc0
    sead::SafeString mBreathPartsKey2_s{};
    // aitree_variable at offset 0xd0
    int* mLynelAIFlags_a{};
};

}  // namespace uking::ai
