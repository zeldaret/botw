#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerDoorPullOpen : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerDoorPullOpen, PlayerAction)
public:
    explicit PlayerDoorPullOpen(const InitArg& arg);
    ~PlayerDoorPullOpen() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
