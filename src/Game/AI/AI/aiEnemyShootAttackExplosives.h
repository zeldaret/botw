#pragma once

#include "Game/AI/AI/aiEnemyBaseArrowAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyShootAttackExplosives : public EnemyBaseArrowAttack {
    SEAD_RTTI_OVERRIDE(EnemyShootAttackExplosives, EnemyBaseArrowAttack)
public:
    explicit EnemyShootAttackExplosives(const InitArg& arg);
    ~EnemyShootAttackExplosives() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const float* mExplosivesAvoidDist_s{};
    // static_param at offset 0x58
    const float* mTurnStartAng_s{};
};

}  // namespace uking::ai
