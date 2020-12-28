#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshRun : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshRun, NavMeshAction)
public:
    explicit NavMeshRun(const InitArg& arg);

protected:
};

}  // namespace uking::action
