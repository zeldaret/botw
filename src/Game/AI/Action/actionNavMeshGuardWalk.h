#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGuardWalk : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshGuardWalk, NavMeshAction)
public:
    explicit NavMeshGuardWalk(const InitArg& arg);
    ~NavMeshGuardWalk() override;

protected:
};

}  // namespace uking::action
