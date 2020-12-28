#pragma once

#include "Game/AI/Action/actionGrab.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabRight : public Grab {
    SEAD_RTTI_OVERRIDE(GrabRight, Grab)
public:
    explicit GrabRight(const InitArg& arg);

protected:
};

}  // namespace uking::action
