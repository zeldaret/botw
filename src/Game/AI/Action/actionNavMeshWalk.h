#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshWalk : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshWalk, NavMeshAction)
public:
    explicit NavMeshWalk(const InitArg& arg);

protected:
};

}  // namespace uking::action
