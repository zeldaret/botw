#pragma once

#include "Game/Actor/AI/aiEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class UnarmedWeaponEquipableEnemyAct : public EnemySearch {
    SEAD_RTTI_OVERRIDE(UnarmedWeaponEquipableEnemyAct, EnemySearch)
public:
    explicit UnarmedWeaponEquipableEnemyAct(const InitArg& arg);
    ~UnarmedWeaponEquipableEnemyAct() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
