#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutAfterJust : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutAfterJust, PlayerAction)
public:
    explicit PlayerCutAfterJust(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSlowContTime_s{};
    // static_param at offset 0x28
    const float* mLastCutAcceptTime_s{};
    // static_param at offset 0x30
    const float* mLastCutAcceptTimeLSword_s{};
    // static_param at offset 0x38
    const float* mLastCutAcceptTimeSpear_s{};
    // static_param at offset 0x40
    const float* mForceSlowTime_s{};
};

}  // namespace uking::action
