#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSideStep : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSideStep, PlayerAction)
public:
    explicit PlayerSideStep(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeedF_s{};
    // static_param at offset 0x28
    const float* mHeight_s{};
    // static_param at offset 0x30
    const float* mFSpeedF_s{};
    // static_param at offset 0x38
    const float* mFHeight_s{};
    // static_param at offset 0x40
    const float* mUHeight_s{};
    // static_param at offset 0x48
    const float* mNoDamageTime_s{};
    // static_param at offset 0x50
    const float* mJustAvoidTime_s{};
    // static_param at offset 0x58
    const float* mForceSlowTime_s{};
    // static_param at offset 0x60
    const float* mMySlowStartFrame_s{};
};

}  // namespace uking::action
