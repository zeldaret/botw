#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyPursuingBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemyPursuingBattle, EnemyBattle)
public:
    explicit EnemyPursuingBattle(const InitArg& arg);
    ~EnemyPursuingBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x98
    const int* mPursuingAttackIntervalRand_s{};
    // static_param at offset 0xa0
    const float* mPursuingAttackStartAng_s{};
};

}  // namespace uking::ai
