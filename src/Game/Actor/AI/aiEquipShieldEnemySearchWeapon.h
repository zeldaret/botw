#pragma once

#include "Game/Actor/AI/aiEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EquipShieldEnemySearchWeapon : public EnemySearch {
    SEAD_RTTI_OVERRIDE(EquipShieldEnemySearchWeapon, EnemySearch)
public:
    explicit EquipShieldEnemySearchWeapon(const InitArg& arg);
    ~EquipShieldEnemySearchWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
