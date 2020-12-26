#pragma once

#include "Game/AI/Action/actionGiantOneHandActionWithLegTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantOneHandAttackWithLegTurn : public GiantOneHandActionWithLegTurn {
    SEAD_RTTI_OVERRIDE(GiantOneHandAttackWithLegTurn, GiantOneHandActionWithLegTurn)
public:
    explicit GiantOneHandAttackWithLegTurn(const InitArg& arg);
    ~GiantOneHandAttackWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
