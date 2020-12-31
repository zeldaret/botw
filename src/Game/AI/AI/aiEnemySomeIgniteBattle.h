#pragma once

#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemySomeIgniteBattle : public BreathAttackEnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemySomeIgniteBattle, BreathAttackEnemyBattle)
public:
    explicit EnemySomeIgniteBattle(const InitArg& arg);
    ~EnemySomeIgniteBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb0
    const int* mIgniteNum_s{};
};

}  // namespace uking::ai
