#pragma once

#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DynTgBreathAttackEnemyBattle : public BreathAttackEnemyBattle {
    SEAD_RTTI_OVERRIDE(DynTgBreathAttackEnemyBattle, BreathAttackEnemyBattle)
public:
    explicit DynTgBreathAttackEnemyBattle(const InitArg& arg);
    ~DynTgBreathAttackEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
