#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyBattleWithAreaCheck : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(EnemyBattleWithAreaCheck, EnemyBattle)
public:
    explicit EnemyBattleWithAreaCheck(const InitArg& arg);
    ~EnemyBattleWithAreaCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mWeaponIdx_s{};
    // static_param at offset 0x98
    const float* mAttackVMin_s{};
    // static_param at offset 0xa0
    const float* mAttackVMax_s{};
    // static_param at offset 0xa8
    const float* mAttackFar_s{};
};

}  // namespace uking::ai
