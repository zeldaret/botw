#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoWeaponAttack : public ForkNoWeaponAttackBase {
    SEAD_RTTI_OVERRIDE(ForkNoWeaponAttack, ForkNoWeaponAttackBase)
public:
    explicit ForkNoWeaponAttack(const InitArg& arg);
    ~ForkNoWeaponAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const int* mTargetBone_s{};
    // static_param at offset 0xb8
    const int* mSeqBank_s{};
};

}  // namespace uking::action
