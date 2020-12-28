#pragma once

#include "Game/AI/Action/actionPlayerFall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerTwiceJump : public PlayerFall {
    SEAD_RTTI_OVERRIDE(PlayerTwiceJump, PlayerFall)
public:
    explicit PlayerTwiceJump(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const float* mJumpHeight_s{};
};

}  // namespace uking::action
