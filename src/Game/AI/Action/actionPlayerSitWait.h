#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSitWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSitWait, PlayerAction)
public:
    explicit PlayerSitWait(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAutoRecoverRate_s{};
    // static_param at offset 0x28
    const float* mEnergyAutoRecover_s{};
};

}  // namespace uking::action
