#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerDiveMove : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerDiveMove, PlayerAction)
public:
    explicit PlayerDiveMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAnmDrivenDist_s{};
    // static_param at offset 0x28
    const float* mFinishDist_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
