#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BreathAttackEnemyBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BreathAttackEnemyBattle, ksys::act::ai::Ai)
public:
    explicit BreathAttackEnemyBattle(const InitArg& arg);
    ~BreathAttackEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mEnlargeTime_s{};
    // static_param at offset 0x40
    const float* mAttackAngle_s{};
    // static_param at offset 0x48
    const float* mAttackRatio_s{};
    // static_param at offset 0x50
    const float* mBreathSize_s{};
    // static_param at offset 0x58
    const float* mAttackIntervalIntensity_s{};
    // static_param at offset 0x60
    const int* mGlobalNoAtkTime_s{};
    // static_param at offset 0x68
    const bool* mIsEndAfterAttack_s{};
    // static_param at offset 0x70
    const bool* mIsDeleteBreath_s{};
    // static_param at offset 0x78
    const bool* mIsUpdateNoticeState_s{};
    // static_param at offset 0x80
    sead::SafeString mBreathName_s{};
};

}  // namespace uking::ai
