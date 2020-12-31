#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelCloseBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(LynelCloseBattle, EnemyBattle)
public:
    explicit LynelCloseBattle(const InitArg& arg);
    ~LynelCloseBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mBackAngleAction_s{};
    // static_param at offset 0x98
    const float* mBackAngle_s{};
    // aitree_variable at offset 0xa0
    int* mLynelAIFlags_a{};
};

}  // namespace uking::ai
