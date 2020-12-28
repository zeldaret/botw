#pragma once

#include "Game/AI/Action/actionEquipedAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedDefaultWindWeapon : public EquipedAction {
    SEAD_RTTI_OVERRIDE(EquipedDefaultWindWeapon, EquipedAction)
public:
    explicit EquipedDefaultWindWeapon(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mWindRadius_s{};
    // static_param at offset 0x50
    const float* mWindRadiusLarge_s{};
    // static_param at offset 0x58
    const float* mWindSpeed_s{};
    // static_param at offset 0x60
    const float* mWindSpeedLarge_s{};
    // static_param at offset 0x68
    const float* mWindSpeedRate1_s{};
    // static_param at offset 0x70
    const float* mWindSpeedRate2_s{};
    // static_param at offset 0x78
    const float* mWindSpeedRate3_s{};
    // static_param at offset 0x80
    const float* mWindLength_s{};
    // static_param at offset 0x88
    const float* mCapsuleMaxSpeed_s{};
    // static_param at offset 0x90
    const float* mWindReduceRate_s{};
    // static_param at offset 0x98
    const float* mWindReduceRateLarge_s{};
    // static_param at offset 0xa0
    const float* mWindFlyingDist_s{};
    // static_param at offset 0xa8
    const float* mWindFlyingDistLarge_s{};
    // static_param at offset 0xb0
    const float* mWindFlyingDistRate1_s{};
    // static_param at offset 0xb8
    const float* mWindFlyingDistRate2_s{};
    // static_param at offset 0xc0
    const float* mWindFlyingDistRate3_s{};
};

}  // namespace uking::action
