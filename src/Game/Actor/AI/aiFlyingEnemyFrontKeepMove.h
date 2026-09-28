#pragma once

#include "Game/Actor/AI/aiFlyingEnemyDistanceKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyFrontKeepMove : public FlyingEnemyDistanceKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemyFrontKeepMove, FlyingEnemyDistanceKeepMove)
public:
    explicit FlyingEnemyFrontKeepMove(const InitArg& arg);
    ~FlyingEnemyFrontKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
