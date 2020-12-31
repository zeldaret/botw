#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniRangeKeepMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(GuardianMiniRangeKeepMove, EnemyRangeKeepMove)
public:
    explicit GuardianMiniRangeKeepMove(const InitArg& arg);
    ~GuardianMiniRangeKeepMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
