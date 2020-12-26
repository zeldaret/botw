#pragma once

#include "Game/AI/Action/actionPlayerLookAtObjectNow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerTurnAndLookToObjectNow : public PlayerLookAtObjectNow {
    SEAD_RTTI_OVERRIDE(PlayerTurnAndLookToObjectNow, PlayerLookAtObjectNow)
public:
    explicit PlayerTurnAndLookToObjectNow(const InitArg& arg);
    ~PlayerTurnAndLookToObjectNow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
