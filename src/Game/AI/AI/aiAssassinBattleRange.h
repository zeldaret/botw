#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBattleRange : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(AssassinBattleRange, EnemyBattle)
public:
    explicit AssassinBattleRange(const InitArg& arg);
    ~AssassinBattleRange() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mScapeGoatCheckInterval_s{};
    // static_param at offset 0x98
    const int* mServiceCheckInterval_s{};
    // static_param at offset 0xa0
    const int* mServicePer_s{};
    // static_param at offset 0xa8
    const float* mScapeGoatPer_s{};
    // static_param at offset 0xb0
    const float* mServiceDist_s{};
};

}  // namespace uking::ai
