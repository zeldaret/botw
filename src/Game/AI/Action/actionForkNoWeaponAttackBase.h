#pragma once

#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoWeaponAttackBase : public ForkAttackWithWeaponOrWithout {
    SEAD_RTTI_OVERRIDE(ForkNoWeaponAttackBase, ForkAttackWithWeaponOrWithout)
public:
    explicit ForkNoWeaponAttackBase(const InitArg& arg);
    ~ForkNoWeaponAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mAttackType_s{};
    // static_param at offset 0x58
    const float* mAttackPowerScale_s{};
    // static_param at offset 0x60
    const bool* mIsImpulseLarge_s{};
    // static_param at offset 0x68
    const bool* mIsUseAttackParam_s{};
    // static_param at offset 0xa0
    sead::SafeString mChmName1_s{};
};

}  // namespace uking::action
