#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ShootingEnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(ShootingEnemyBattle, EnemyBattle)
public:
    explicit ShootingEnemyBattle(const InitArg& arg);
    ~ShootingEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mOutScreenAttackNum_s{};
    // static_param at offset 0x98
    const float* mOutScreenDist_s{};
    // static_param at offset 0xa0
    const float* mOutScrnAtkOffset_s{};
    // static_param at offset 0xa8
    const float* mOutScrnAtkOffsetY_s{};
};

}  // namespace uking::ai
