#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemFireREnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(GolemFireREnemyBattle, EnemyBattle)
public:
    explicit GolemFireREnemyBattle(const InitArg& arg);
    ~GolemFireREnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mPlayerRecoverFromFallFrames_s{};
};

}  // namespace uking::ai
