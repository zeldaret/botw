#pragma once

#include "Game/Actor/AI/aiGiantEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantFindPlayer : public GiantEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(ForestGiantFindPlayer, GiantEnemyFindPlayer)
public:
    explicit ForestGiantFindPlayer(const InitArg& arg);
    ~ForestGiantFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
