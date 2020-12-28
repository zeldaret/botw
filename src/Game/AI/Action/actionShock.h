#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Shock : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Shock, ksys::act::ai::Action)
public:
    explicit Shock(const InitArg& arg);
    ~Shock() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mKnockBackTime_s{};
    // static_param at offset 0x28
    const int* mWeaponIdx_s{};
    // static_param at offset 0x30
    const float* mHitImpactForce_s{};
    // static_param at offset 0x38
    const float* mVelReduce_s{};
    // static_param at offset 0x40
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x48
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x50
    const int* mASSlot_s{};
    // static_param at offset 0x58
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
