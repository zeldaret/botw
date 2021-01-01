#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHoldUpDRC : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHoldUpDRC, PlayerAction)
public:
    explicit PlayerHoldUpDRC(const InitArg& arg);
    ~PlayerHoldUpDRC() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsContinued_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
