#pragma once

#include "Game/AI/AI/aiEnemyVacuumBombSelectBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyVacuumBombSelect : public EnemyVacuumBombSelectBase {
    SEAD_RTTI_OVERRIDE(EnemyVacuumBombSelect, EnemyVacuumBombSelectBase)
public:
    explicit EnemyVacuumBombSelect(const InitArg& arg);
    ~EnemyVacuumBombSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
