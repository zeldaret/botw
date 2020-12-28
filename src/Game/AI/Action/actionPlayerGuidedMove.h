#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGuidedMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGuidedMove, PlayerAction)
public:
    explicit PlayerGuidedMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDecSpdDist_s{};
    // dynamic_param at offset 0x28
    float* mStickValue_d{};
    // static_param at offset 0x30
    const float* mForceTurnDist_s{};
};

}  // namespace uking::action
