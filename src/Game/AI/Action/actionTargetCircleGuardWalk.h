#pragma once

#include "Game/AI/Action/actionTargetCircle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TargetCircleGuardWalk : public TargetCircle {
    SEAD_RTTI_OVERRIDE(TargetCircleGuardWalk, TargetCircle)
public:
    explicit TargetCircleGuardWalk(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
