#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDropWeapon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkDropWeapon, ksys::act::ai::Action)
public:
    explicit ForkDropWeapon(const InitArg& arg);
    ~ForkDropWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mWeaponDropSpeedXZ_s{};
    // static_param at offset 0x30
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x38
    const float* mAngleOffsetY_s{};
    // static_param at offset 0x40
    const bool* mChemReset_s{};
};

}  // namespace uking::action
