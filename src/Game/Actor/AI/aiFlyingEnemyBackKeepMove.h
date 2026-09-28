#pragma once

#include "Game/Actor/AI/aiFlyingEnemyDistanceKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyBackKeepMove : public FlyingEnemyDistanceKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemyBackKeepMove, FlyingEnemyDistanceKeepMove)
public:
    explicit FlyingEnemyBackKeepMove(const InitArg& arg);
    ~FlyingEnemyBackKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
