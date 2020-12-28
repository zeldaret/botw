#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHellNoFade : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHellNoFade, PlayerAction)
public:
    explicit PlayerHellNoFade(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mCleaningTime_s{};
};

}  // namespace uking::action
