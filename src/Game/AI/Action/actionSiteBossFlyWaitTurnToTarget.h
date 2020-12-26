#pragma once

#include "Game/AI/Action/actionLastBossFlyWaitTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossFlyWaitTurnToTarget : public LastBossFlyWaitTurnToTarget {
    SEAD_RTTI_OVERRIDE(SiteBossFlyWaitTurnToTarget, LastBossFlyWaitTurnToTarget)
public:
    explicit SiteBossFlyWaitTurnToTarget(const InitArg& arg);
    ~SiteBossFlyWaitTurnToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
