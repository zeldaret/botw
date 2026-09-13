#pragma once

#include "Game/Actor/AI/aiEnemyFeintBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IceEnemyFeintBattle : public EnemyFeintBattle {
    SEAD_RTTI_OVERRIDE(IceEnemyFeintBattle, EnemyFeintBattle)
public:
    explicit IceEnemyFeintBattle(const InitArg& arg);
    ~IceEnemyFeintBattle() override;

    void loadParams_() override;

protected:
};

}  // namespace uking::ai
