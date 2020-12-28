#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAttackWithWeaponOrWithout : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAttackWithWeaponOrWithout, ksys::act::ai::Action)
public:
    explicit ForkAttackWithWeaponOrWithout(const InitArg& arg);
    ~ForkAttackWithWeaponOrWithout() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const int* mAttackIntensity_s{};
    // static_param at offset 0x28
    const bool* mIsGuardPierce_s{};
    // static_param at offset 0x30
    const bool* mIsForceGuardBreak_s{};
    // static_param at offset 0x38
    const bool* mIsIniviciblePierce_s{};
    // static_param at offset 0x40
    const bool* mIsHeavy_s{};
    // static_param at offset 0x48
    const bool* mIsHammer_s{};
};

}  // namespace uking::action
