#pragma once

#include "Game/AI/Action/actionForkMoveDistanceCheckByDistance.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkMoveDistanceCheckByMapUnit : public ForkMoveDistanceCheckByDistance {
    SEAD_RTTI_OVERRIDE(ForkMoveDistanceCheckByMapUnit, ForkMoveDistanceCheckByDistance)
public:
    explicit ForkMoveDistanceCheckByMapUnit(const InitArg& arg);
    ~ForkMoveDistanceCheckByMapUnit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x48
    const float* mRange_m{};
};

}  // namespace uking::action
