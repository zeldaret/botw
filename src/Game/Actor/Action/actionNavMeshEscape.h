#pragma once

#include "Game/Actor/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshEscape : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshEscape, NavMeshAction)
public:
    explicit NavMeshEscape(const InitArg& arg);

protected:
};

}  // namespace uking::action
