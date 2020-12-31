#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OneMemoryMagicBattleBase : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(OneMemoryMagicBattleBase, EnemyBattle)
public:
    explicit OneMemoryMagicBattleBase(const InitArg& arg);
    ~OneMemoryMagicBattleBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mEnlargeTime_s{};
    // static_param at offset 0x98
    const int* mMagicPer_s{};
    // static_param at offset 0xa0
    const int* mAttackPowDirect_s{};
    // static_param at offset 0xa8
    const float* mAttackRatio_s{};
    // static_param at offset 0xb0
    const float* mBreathSize_s{};
    // static_param at offset 0xb8
    sead::SafeString mMagicName_s{};
};

}  // namespace uking::ai
