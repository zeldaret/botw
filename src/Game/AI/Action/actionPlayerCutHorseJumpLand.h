#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCutHorseJumpLand : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCutHorseJumpLand, PlayerAction)
public:
    explicit PlayerCutHorseJumpLand(const InitArg& arg);
    ~PlayerCutHorseJumpLand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
