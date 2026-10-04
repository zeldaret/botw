#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoWeaponAttackParamWeapon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkNoWeaponAttackParamWeapon, ksys::act::ai::Action)
public:
    explicit ForkNoWeaponAttackParamWeapon(const InitArg& arg);
    ~ForkNoWeaponAttackParamWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mSeqBank_s{};
    // static_param at offset 0x30
    const int* mTargetBone_s{};
    // static_param at offset 0x38
    const int* mAttackIntensity_s{};
    // static_param at offset 0x40
    sead::SafeString mAtkBodyName_s{};
};

}  // namespace uking::action
