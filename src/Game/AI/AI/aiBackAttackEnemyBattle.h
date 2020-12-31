#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BackAttackEnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(BackAttackEnemyBattle, EnemyBattle)
public:
    explicit BackAttackEnemyBattle(const InitArg& arg);
    ~BackAttackEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mBackAttackAngle_s{};
};

}  // namespace uking::ai
