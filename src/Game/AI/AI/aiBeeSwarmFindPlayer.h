#pragma once

#include "Game/AI/AI/aiFlyingEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeeSwarmFindPlayer : public FlyingEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(BeeSwarmFindPlayer, FlyingEnemyFindPlayer)
public:
    explicit BeeSwarmFindPlayer(const InitArg& arg);
    ~BeeSwarmFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
