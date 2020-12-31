#pragma once

#include "Game/AI/AI/aiEnemyWatchKeepingWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressWatchKeepingWait : public EnemyWatchKeepingWait {
    SEAD_RTTI_OVERRIDE(EnemyFortressWatchKeepingWait, EnemyWatchKeepingWait)
public:
    explicit EnemyFortressWatchKeepingWait(const InitArg& arg);
    ~EnemyFortressWatchKeepingWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
