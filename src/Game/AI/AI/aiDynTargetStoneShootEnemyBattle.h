#pragma once

#include "Game/AI/AI/aiStoneShootEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DynTargetStoneShootEnemyBattle : public StoneShootEnemyBattle {
    SEAD_RTTI_OVERRIDE(DynTargetStoneShootEnemyBattle, StoneShootEnemyBattle)
public:
    explicit DynTargetStoneShootEnemyBattle(const InitArg& arg);
    ~DynTargetStoneShootEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xb0
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
