#pragma once

#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSeqNoWeaponAttack : public ForkAttackWithWeaponOrWithout {
    SEAD_RTTI_OVERRIDE(ForkSeqNoWeaponAttack, ForkAttackWithWeaponOrWithout)
public:
    explicit ForkSeqNoWeaponAttack(const InitArg& arg);
    ~ForkSeqNoWeaponAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mAttackType_s{};
    // static_param at offset 0x58
    const bool* mIsImpulseLarge_s{};
};

}  // namespace uking::action
