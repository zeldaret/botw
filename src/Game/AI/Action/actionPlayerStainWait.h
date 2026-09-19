#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerStainWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerStainWait, PlayerAction)
public:
    bool isChangeable() const override { return false; }
    explicit PlayerStainWait(const InitArg& arg);
    ~PlayerStainWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
