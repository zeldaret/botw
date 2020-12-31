#pragma once

#include "Game/AI/AI/aiFlyingEnemyKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyBackKeepMove : public FlyingEnemyKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemyBackKeepMove, FlyingEnemyKeepMove)
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
