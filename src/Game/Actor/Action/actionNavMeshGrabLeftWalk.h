#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGrabLeftWalk : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshGrabLeftWalk, NavMeshMoveBase)
public:
    explicit NavMeshGrabLeftWalk(const InitArg& arg);

protected:
};

}  // namespace uking::action
