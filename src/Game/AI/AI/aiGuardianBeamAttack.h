#pragma once

#include "Game/AI/AI/aiGuardianBeamAttackBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianBeamAttack : public GuardianBeamAttackBase {
    SEAD_RTTI_OVERRIDE(GuardianBeamAttack, GuardianBeamAttackBase)
public:
    explicit GuardianBeamAttack(const InitArg& arg);
    ~GuardianBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const float* mLightRadius_s{};
    // static_param at offset 0x88
    const float* mLightLength_s{};
    // static_param at offset 0x90
    const float* mLightLengthOffset_s{};
    // static_param at offset 0x98
    const float* mEarSpeed_s{};
    // static_param at offset 0xa0
    const bool* mAdjustRadius_s{};
};

}  // namespace uking::ai
