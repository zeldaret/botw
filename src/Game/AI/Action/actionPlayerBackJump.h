#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerBackJump : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerBackJump, PlayerAction)
public:
    explicit PlayerBackJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mBJSpeedF_s{};
    // static_param at offset 0x28
    const float* mBJHeight_s{};
    // static_param at offset 0x30
    const float* mNoDamageTime_s{};
    // static_param at offset 0x38
    const float* mJustAvoidTime_s{};
    // static_param at offset 0x40
    const float* mForceSlowTime_s{};
    // static_param at offset 0x48
    const float* mMySlowStartFrame_s{};
    // dynamic_param at offset 0x50
    bool* mEnableSwordInput_d{};
};

}  // namespace uking::action
