#pragma once

#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWeaponAttackBase : public ForkAttackWithWeaponOrWithout {
    SEAD_RTTI_OVERRIDE(ForkWeaponAttackBase, ForkAttackWithWeaponOrWithout)
public:
    explicit ForkWeaponAttackBase(const InitArg& arg);
    ~ForkWeaponAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mSeqBank_s{};
    // static_param at offset 0x58
    const int* mTargetBone_s{};
    // static_param at offset 0x60
    const bool* mIsNoRod_s{};
};

}  // namespace uking::action
