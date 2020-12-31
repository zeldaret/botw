#pragma once

#include "Game/AI/AI/aiGuardianMiniBeamAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeamToExplosives : public GuardianMiniBeamAttack {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamToExplosives, GuardianMiniBeamAttack)
public:
    explicit GuardianMiniBeamToExplosives(const InitArg& arg);
    ~GuardianMiniBeamToExplosives() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x2d8
    const float* mExplosivesAvoidDist_s{};
    // dynamic_param at offset 0x2e0
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
