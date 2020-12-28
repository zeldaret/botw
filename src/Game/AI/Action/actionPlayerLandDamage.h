#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLandDamage : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerLandDamage, PlayerAction)
public:
    explicit PlayerLandDamage(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWaitTimeMin_s{};
    // static_param at offset 0x28
    const float* mWaitTimeMax_s{};
    // static_param at offset 0x30
    const float* mDeadHeight_s{};
    // static_param at offset 0x38
    const int* mDamageMin_s{};
};

}  // namespace uking::action
