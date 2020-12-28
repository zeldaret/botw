#pragma once

#include "Game/AI/Action/actionJumpTo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshJump : public JumpTo {
    SEAD_RTTI_OVERRIDE(NavMeshJump, JumpTo)
public:
    explicit NavMeshJump(const InitArg& arg);

protected:
};

}  // namespace uking::action
