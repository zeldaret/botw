#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGuardWalk : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshGuardWalk, NavMeshMoveBase)
public:
    explicit NavMeshGuardWalk(const InitArg& arg);
    ~NavMeshGuardWalk() override;

protected:
};

}  // namespace uking::action
