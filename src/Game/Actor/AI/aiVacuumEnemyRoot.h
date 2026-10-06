#pragma once

#include "Game/Actor/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class VacuumEnemyRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(VacuumEnemyRoot, EnemyRoot)
public:
    explicit VacuumEnemyRoot(const InitArg& arg);
    ~VacuumEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
