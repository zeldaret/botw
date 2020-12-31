#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFeintBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemyFeintBattle, EnemyBattle)
public:
    explicit EnemyFeintBattle(const InitArg& arg);
    ~EnemyFeintBattle() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const bool* mIsAttackEnd_s{};
};

}  // namespace uking::ai
