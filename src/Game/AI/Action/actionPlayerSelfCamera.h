#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSelfCamera : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerSelfCamera, PlayerAction)
public:
    explicit PlayerSelfCamera(const InitArg& arg);
    ~PlayerSelfCamera() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
