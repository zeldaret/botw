#pragma once

#include "Game/AI/AI/aiStoneShootEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantStoneShootBattle : public StoneShootEnemyBattle {
    SEAD_RTTI_OVERRIDE(ForestGiantStoneShootBattle, StoneShootEnemyBattle)
public:
    explicit ForestGiantStoneShootBattle(const InitArg& arg);
    ~ForestGiantStoneShootBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb0
    const int* mShootItemRate1_s{};
    // static_param at offset 0xb8
    const float* mForceAttackArea_s{};
    // static_param at offset 0xc0
    sead::SafeString mShootItemName2_s{};
};

}  // namespace uking::ai
