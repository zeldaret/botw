#pragma once

#include "Game/AI/Action/actionHorseRide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideLoopAttack : public HorseRide {
    SEAD_RTTI_OVERRIDE(HorseRideLoopAttack, HorseRide)
public:
    explicit HorseRideLoopAttack(const InitArg& arg);
    ~HorseRideLoopAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mLoopAttackTime_s{};
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const bool* mIsFinishByAtHit_s{};
    // static_param at offset 0x48
    const bool* mIsNoRodAttack_s{};
    // static_param at offset 0x50
    sead::SafeString mFinishAS_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
