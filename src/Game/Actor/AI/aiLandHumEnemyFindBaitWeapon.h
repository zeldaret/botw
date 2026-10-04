#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyFindBaitWeapon : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LandHumEnemyFindBaitWeapon, ksys::act::ai::Ai)
public:
    explicit LandHumEnemyFindBaitWeapon(const InitArg& arg);
    ~LandHumEnemyFindBaitWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetWeapon_d{};
};

}  // namespace uking::ai
