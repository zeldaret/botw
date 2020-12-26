#pragma once

#include "Game/AI/Action/actionGiantOneHandActionWithLegTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantOneHandPunchWithLegTurn : public GiantOneHandActionWithLegTurn {
    SEAD_RTTI_OVERRIDE(GiantOneHandPunchWithLegTurn, GiantOneHandActionWithLegTurn)
public:
    explicit GiantOneHandPunchWithLegTurn(const InitArg& arg);
    ~GiantOneHandPunchWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
