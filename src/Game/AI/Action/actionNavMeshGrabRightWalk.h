#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGrabRightWalk : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshGrabRightWalk, NavMeshAction)
public:
    explicit NavMeshGrabRightWalk(const InitArg& arg);

protected:
};

}  // namespace uking::action
