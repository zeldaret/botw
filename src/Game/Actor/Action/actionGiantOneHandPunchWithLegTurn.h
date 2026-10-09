#pragma once

#include "Game/Actor/Action/actionOneHandActionWithLegTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantOneHandPunchWithLegTurn : public OneHandActionWithLegTurn {
    SEAD_RTTI_OVERRIDE(GiantOneHandPunchWithLegTurn, OneHandActionWithLegTurn)
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
