#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSwimDash : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSwimDash, PlayerAction)
public:
    explicit PlayerSwimDash(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEnergyDash_s{};
};

}  // namespace uking::action
