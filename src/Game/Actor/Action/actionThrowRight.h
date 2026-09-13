#pragma once

#include "Game/Actor/Action/actionThrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrowRight : public Throw {
    SEAD_RTTI_OVERRIDE(ThrowRight, Throw)
public:
    explicit ThrowRight(const InitArg& arg);

protected:
};

}  // namespace uking::action
