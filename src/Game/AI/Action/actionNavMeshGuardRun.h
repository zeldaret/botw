#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshGuardRun : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshGuardRun, NavMeshAction)
public:
    explicit NavMeshGuardRun(const InitArg& arg);
    ~NavMeshGuardRun() override;

protected:
};

}  // namespace uking::action
