#pragma once

#include "Game/AI/Action/actionHorseRide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideShoot : public HorseRide {
    SEAD_RTTI_OVERRIDE(HorseRideShoot, HorseRide)
public:
    explicit HorseRideShoot(const InitArg& arg);
    ~HorseRideShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mOffsetRangeMin_s{};
    // static_param at offset 0x40
    const float* mOffsetRangeMax_s{};
    // static_param at offset 0x48
    const float* mOffsetRateByDist_s{};
    // static_param at offset 0x50
    const float* mOffsetRangeMinOutOfScreen_s{};
    // static_param at offset 0x58
    const float* mOffsetRangeMaxOutOfScreen_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
