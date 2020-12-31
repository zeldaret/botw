#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideEnemyFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(HorseRideEnemyFindPlayer, EnemyBaseFindPlayer)
public:
    explicit HorseRideEnemyFindPlayer(const InitArg& arg);
    ~HorseRideEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
