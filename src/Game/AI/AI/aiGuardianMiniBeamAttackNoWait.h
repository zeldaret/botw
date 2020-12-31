#pragma once

#include "Game/AI/AI/aiGuardianMiniBeamAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeamAttackNoWait : public GuardianMiniBeamAttack {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamAttackNoWait, GuardianMiniBeamAttack)
public:
    explicit GuardianMiniBeamAttackNoWait(const InitArg& arg);
    ~GuardianMiniBeamAttackNoWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x2d8
    const float* mAttackAngle_s{};
};

}  // namespace uking::ai
