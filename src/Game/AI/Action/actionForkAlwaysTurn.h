#pragma once

#include "Game/AI/Action/actionForkTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysTurn : public ForkTurn {
    SEAD_RTTI_OVERRIDE(ForkAlwaysTurn, ForkTurn)
public:
    explicit ForkAlwaysTurn(const InitArg& arg);
    ~ForkAlwaysTurn() override;

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
