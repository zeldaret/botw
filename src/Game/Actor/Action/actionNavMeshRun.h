#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshRun : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshRun, NavMeshMoveBase)
public:
    explicit NavMeshRun(const InitArg& arg);

protected:
};

}  // namespace uking::action
