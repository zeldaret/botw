#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerPullSword : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerPullSword, PlayerAction)
public:
    explicit PlayerPullSword(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mLifeDecInterval1_s{};
    // static_param at offset 0x30
    const float* mLifeDecInterval2_s{};
    // static_param at offset 0x38
    const float* mLifeDecInterval3_s{};
    // static_param at offset 0x40
    const float* mLifeDecInterval4_s{};
    // static_param at offset 0x48
    const float* mLifeDecInterval5_s{};
    // static_param at offset 0x50
    const float* mInterruptInterval_s{};
    // static_param at offset 0x60
    const int* mSuccessLife_s{};
};

}  // namespace uking::action
