#pragma once

#include "Game/AI/Action/actionForkHoverKeepRotateTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkHoverKeepRotateTurn : public ForkHoverKeepRotateTurnBase {
    SEAD_RTTI_OVERRIDE(ForkHoverKeepRotateTurn, ForkHoverKeepRotateTurnBase)
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
