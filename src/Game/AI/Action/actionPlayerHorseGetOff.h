#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHorseGetOff : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHorseGetOff, PlayerAction)
public:
    explicit PlayerHorseGetOff(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSideFallSpeed_s{};
};

}  // namespace uking::action
