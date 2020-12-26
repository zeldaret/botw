#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoWeaponAttackDirectParam : public ForkNoWeaponAttack {
    SEAD_RTTI_OVERRIDE(ForkNoWeaponAttackDirectParam, ForkNoWeaponAttack)
public:
    explicit ForkNoWeaponAttackDirectParam(const InitArg& arg);
    ~ForkNoWeaponAttackDirectParam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mAttackPower_s{};
    // static_param at offset 0xc8
    const int* mGuardBreakPower_s{};
    // static_param at offset 0xd0
    const int* mImpulse_s{};
};

}  // namespace uking::action
