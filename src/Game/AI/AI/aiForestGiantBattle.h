#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(ForestGiantBattle, EnemyBattle)
public:
    explicit ForestGiantBattle(const InitArg& arg);
    ~ForestGiantBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mForceAttackArea_s{};
};

}  // namespace uking::ai
