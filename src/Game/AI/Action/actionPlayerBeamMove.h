#pragma once

#include "Game/AI/Action/actionWindCutter.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerBeamMove : public WindCutter {
    SEAD_RTTI_OVERRIDE(PlayerBeamMove, WindCutter)
public:
    explicit PlayerBeamMove(const InitArg& arg);
    ~PlayerBeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
