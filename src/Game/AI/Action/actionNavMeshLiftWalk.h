#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshLiftWalk : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshLiftWalk, NavMeshAction)
public:
    explicit NavMeshLiftWalk(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
