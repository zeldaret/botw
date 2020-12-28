#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWeaponShockWave : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkWeaponShockWave, ksys::act::ai::Action)
public:
    explicit ForkWeaponShockWave(const InitArg& arg);
    ~ForkWeaponShockWave() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
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
    const float* mShockWaveRadius_s{};
    // static_param at offset 0x40
    const float* mUnderRayLength_s{};
};

}  // namespace uking::action
