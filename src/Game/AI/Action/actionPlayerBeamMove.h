#pragma once

#include "Game/AI/Action/actionWindCutter.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerBeamMove : public WindCutter {
    SEAD_RTTI_OVERRIDE(PlayerBeamMove, WindCutter)
public:
    explicit PlayerBeamMove(const InitArg& arg);
    ~PlayerBeamMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
