#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowIgniteToSelfPos : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowIgniteToSelfPos, RotateTurnToTarget)
public:
    explicit FollowIgniteToSelfPos(const InitArg& arg);
    ~FollowIgniteToSelfPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
