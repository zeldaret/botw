#pragma once

#include "Game/AI/AI/aiFlyingEnemyKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyFrontKeepMove : public FlyingEnemyKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemyFrontKeepMove, FlyingEnemyKeepMove)
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
