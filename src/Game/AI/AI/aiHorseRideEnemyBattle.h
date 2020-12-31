#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideEnemyBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(HorseRideEnemyBattle, EnemyBattle)
public:
    explicit HorseRideEnemyBattle(const InitArg& arg);
    ~HorseRideEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mWeaponIdx_s{};
    // static_param at offset 0x98
    const float* mAttackRadius_s{};
};

}  // namespace uking::ai
