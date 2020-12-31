#pragma once

#include "Game/AI/AI/aiShootingEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideShootingEnemyBattle : public ShootingEnemyBattle {
    SEAD_RTTI_OVERRIDE(HorseRideShootingEnemyBattle, ShootingEnemyBattle)
public:
    explicit HorseRideShootingEnemyBattle(const InitArg& arg);
    ~HorseRideShootingEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const int* mTrackTime_s{};
    // static_param at offset 0xd0
    const int* mTrackTimeRand_s{};
    // static_param at offset 0xd8
    const int* mSlowTime_s{};
    // static_param at offset 0xe0
    const int* mSlowTimeRand_s{};
};

}  // namespace uking::ai
