#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHangWallCatch : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHangWallCatch, PlayerAction)
public:
    explicit PlayerHangWallCatch(const InitArg& arg);
    ~PlayerHangWallCatch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
