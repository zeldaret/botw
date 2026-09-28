#pragma once

#include "Game/Actor/Action/actionASPlayRotateTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowIgniteToSelfPos : public ASPlayRotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowIgniteToSelfPos, ASPlayRotateTurnToTarget)
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
