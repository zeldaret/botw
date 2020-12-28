#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHorseJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHorseJump, PlayerAction)
public:
    explicit PlayerHorseJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mJumpHeight_s{};
    // static_param at offset 0x28
    const float* mJumpSpeedF_s{};
    // static_param at offset 0x30
    const float* mJumpSpeedF2_s{};
    // static_param at offset 0x38
    const float* mJumpSpeedF3_s{};
    // static_param at offset 0x40
    const float* mJumpSpeedF4_s{};
    // static_param at offset 0x48
    const float* mJumpMaxSpeedF_s{};
    // static_param at offset 0x50
    const float* mAimDistOffset_s{};
    // dynamic_param at offset 0x58
    int* mJumpGear_d{};
    // dynamic_param at offset 0x60
    bool* mIsLargeHorse_d{};
};

}  // namespace uking::action
