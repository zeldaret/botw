#pragma once

#include "Game/AI/Action/actionHorseRide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideArrowReload : public HorseRide {
    SEAD_RTTI_OVERRIDE(HorseRideArrowReload, HorseRide)
public:
    explicit HorseRideArrowReload(const InitArg& arg);
    ~HorseRideArrowReload() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mRotRatio_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
