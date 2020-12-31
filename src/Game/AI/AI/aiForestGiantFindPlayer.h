#pragma once

#include "Game/AI/AI/aiLargeEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantFindPlayer : public LargeEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(ForestGiantFindPlayer, LargeEnemyFindPlayer)
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
