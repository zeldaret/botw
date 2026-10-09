#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGuardRun : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshGuardRun, NavMeshMoveBase)
public:
    explicit NavMeshGuardRun(const InitArg& arg);
    ~NavMeshGuardRun() override;

protected:
};

}  // namespace uking::action
