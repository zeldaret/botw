#pragma once

#include "Game/Actor/Action/actionForkKeepRotateTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkHoverKeepRotateTurn : public ForkKeepRotateTurn {
    SEAD_RTTI_OVERRIDE(ForkHoverKeepRotateTurn, ForkKeepRotateTurn)
public:
    explicit ForkHoverKeepRotateTurn(const InitArg& arg);
    ~ForkHoverKeepRotateTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
