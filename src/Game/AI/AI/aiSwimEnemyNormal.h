#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwimEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(SwimEnemyNormal, EnemyNormal)
public:
    explicit SwimEnemyNormal(const InitArg& arg);
    ~SwimEnemyNormal() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
