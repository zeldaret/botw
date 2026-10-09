#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshEscape : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshEscape, NavMeshMoveBase)
public:
    explicit NavMeshEscape(const InitArg& arg);

protected:
};

}  // namespace uking::action
