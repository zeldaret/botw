#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkMoveDistanceCheckByDistance : public Fork {
    SEAD_RTTI_OVERRIDE(ForkMoveDistanceCheckByDistance, Fork)
public:
    explicit ForkMoveDistanceCheckByDistance(const InitArg& arg);
    ~ForkMoveDistanceCheckByDistance() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mIsCheckOnlyXZ_s{};
};

}  // namespace uking::action
