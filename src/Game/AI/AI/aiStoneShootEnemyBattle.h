#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneShootEnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(StoneShootEnemyBattle, EnemyBattle)
public:
    explicit StoneShootEnemyBattle(const InitArg& arg);
    ~StoneShootEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    sead::SafeString mShootItemName_s{};
};

}  // namespace uking::ai
