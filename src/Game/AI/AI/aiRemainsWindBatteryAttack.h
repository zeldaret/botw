#pragma once

#include "Game/AI/AI/aiGuardianBeamAttackBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWindBatteryAttack : public GuardianBeamAttackBase {
    SEAD_RTTI_OVERRIDE(RemainsWindBatteryAttack, GuardianBeamAttackBase)
public:
    explicit RemainsWindBatteryAttack(const InitArg& arg);
    ~RemainsWindBatteryAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
