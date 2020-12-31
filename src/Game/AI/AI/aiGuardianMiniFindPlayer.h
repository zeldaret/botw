#pragma once

#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniFindPlayer : public LandHumEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(GuardianMiniFindPlayer, LandHumEnemyFindPlayer)
public:
    explicit GuardianMiniFindPlayer(const InitArg& arg);
    ~GuardianMiniFindPlayer() override;

    void loadParams_() override;

protected:
};

}  // namespace uking::ai
