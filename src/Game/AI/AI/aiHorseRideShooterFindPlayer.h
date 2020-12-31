#pragma once

#include "Game/AI/AI/aiSimpleShootingEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideShooterFindPlayer : public SimpleShootingEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(HorseRideShooterFindPlayer, SimpleShootingEnemyFindPlayer)
public:
    explicit HorseRideShooterFindPlayer(const InitArg& arg);
    ~HorseRideShooterFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
