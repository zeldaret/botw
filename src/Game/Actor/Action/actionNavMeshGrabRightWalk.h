#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGrabRightWalk : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshGrabRightWalk, NavMeshMoveBase)
public:
    explicit NavMeshGrabRightWalk(const InitArg& arg);

protected:
};

}  // namespace uking::action
