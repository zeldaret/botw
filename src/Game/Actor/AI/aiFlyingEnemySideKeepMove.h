#pragma once

#include "Game/Actor/AI/aiFlyingEnemyDistanceKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemySideKeepMove : public FlyingEnemyDistanceKeepMove {
    SEAD_RTTI_OVERRIDE(FlyingEnemySideKeepMove, FlyingEnemyDistanceKeepMove)
public:
    explicit FlyingEnemySideKeepMove(const InitArg& arg);
    ~FlyingEnemySideKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const int* mSideDirType_s{};
};

}  // namespace uking::ai
