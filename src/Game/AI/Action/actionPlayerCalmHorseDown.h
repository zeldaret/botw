#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCalmHorseDown : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerCalmHorseDown, ksys::act::ai::Action)
public:
    explicit PlayerCalmHorseDown(const InitArg& arg);
    ~PlayerCalmHorseDown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPlayCalmDownAnimFrames_s{};
    // static_param at offset 0x28
    const float* mEnergyDecreasePerSec_s{};
    // dynamic_param at offset 0x30
    bool* mHasToPlayRidingOnAS_d{};
};

}  // namespace uking::action
