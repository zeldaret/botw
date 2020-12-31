#pragma once

#include "Game/AI/AI/aiFlyingEnemySideKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyDiagonallyKeepMove : public FlyingEnemySideKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemyDiagonallyKeepMove, FlyingEnemySideKeepMove)
public:
    explicit FlyingEnemyDiagonallyKeepMove(const InitArg& arg);
    ~FlyingEnemyDiagonallyKeepMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa8
    const float* mDiagAngle_s{};
};

}  // namespace uking::ai
