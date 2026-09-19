#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerGrabWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerGrabWait, PlayerAction)
public:
    bool isChangeable() const override { return false; }
    explicit PlayerGrabWait(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
