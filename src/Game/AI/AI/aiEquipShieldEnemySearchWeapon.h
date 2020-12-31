#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearchWeapon.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EquipShieldEnemySearchWeapon : public UnarmedEnemySearchWeapon {
    SEAD_RTTI_OVERRIDE(EquipShieldEnemySearchWeapon, UnarmedEnemySearchWeapon)
public:
    explicit EquipShieldEnemySearchWeapon(const InitArg& arg);
    ~EquipShieldEnemySearchWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
