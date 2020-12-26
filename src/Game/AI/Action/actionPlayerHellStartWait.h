#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerHellStartWait : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerHellStartWait, PlayerAction)
public:
    explicit PlayerHellStartWait(const InitArg& arg);
    ~PlayerHellStartWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
