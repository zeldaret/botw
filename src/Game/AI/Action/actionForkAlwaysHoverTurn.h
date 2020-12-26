#pragma once

#include "Game/AI/Action/actionForkAlwaysTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysHoverTurn : public ForkAlwaysTurn {
    SEAD_RTTI_OVERRIDE(ForkAlwaysHoverTurn, ForkAlwaysTurn)
public:
    explicit ForkAlwaysHoverTurn(const InitArg& arg);
    ~ForkAlwaysHoverTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
