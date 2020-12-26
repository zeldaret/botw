#pragma once

#include "Game/AI/Action/actionHorseRideLookWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideAttack : public HorseRideLookWait {
    SEAD_RTTI_OVERRIDE(HorseRideAttack, HorseRideLookWait)
public:
    explicit HorseRideAttack(const InitArg& arg);
    ~HorseRideAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mWeaponIdx_s{};
    // static_param at offset 0x58
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x60
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x68
    const float* mJustAvoidAngle_s{};
};

}  // namespace uking::action
