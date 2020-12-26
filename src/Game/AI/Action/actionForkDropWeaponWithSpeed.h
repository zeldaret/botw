#pragma once

#include "Game/AI/Action/actionForkDropWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDropWeaponWithSpeed : public ForkDropWeapon {
    SEAD_RTTI_OVERRIDE(ForkDropWeaponWithSpeed, ForkDropWeapon)
public:
    explicit ForkDropWeaponWithSpeed(const InitArg& arg);
    ~ForkDropWeaponWithSpeed() override;

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
