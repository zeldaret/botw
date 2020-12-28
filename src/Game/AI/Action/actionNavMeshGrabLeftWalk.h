#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGrabLeftWalk : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshGrabLeftWalk, NavMeshAction)
public:
    explicit NavMeshGrabLeftWalk(const InitArg& arg);

protected:
};

}  // namespace uking::action
