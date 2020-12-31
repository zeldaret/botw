#pragma once

#include "Game/AI/AI/aiEnemyVacuumBombSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyVacuumChangeItemSelect : public EnemyVacuumBombSelect {
    SEAD_RTTI_OVERRIDE(EnemyVacuumChangeItemSelect, EnemyVacuumBombSelect)
public:
    explicit EnemyVacuumChangeItemSelect(const InitArg& arg);
    ~EnemyVacuumChangeItemSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
