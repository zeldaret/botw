#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSuperBlow : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSuperBlow, PlayerAction)
public:
    explicit PlayerSuperBlow(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitSpeed_s{};
    // static_param at offset 0x28
    const float* mJumpHeight_s{};
    // static_param at offset 0x30
    const float* mDecSpeed_s{};
    // static_param at offset 0x38
    const float* mNoRagdollTime_s{};
};

}  // namespace uking::action
