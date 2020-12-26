#pragma once

#include "Game/AI/Action/actionForkAlwaysTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTurnASHold : public ForkAlwaysTurn {
    SEAD_RTTI_OVERRIDE(ForkTurnASHold, ForkAlwaysTurn)
public:
    explicit ForkTurnASHold(const InitArg& arg);
    ~ForkTurnASHold() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
