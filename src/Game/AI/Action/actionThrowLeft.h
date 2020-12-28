#pragma once

#include "Game/AI/Action/actionThrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrowLeft : public Throw {
    SEAD_RTTI_OVERRIDE(ThrowLeft, Throw)
public:
    explicit ThrowLeft(const InitArg& arg);

protected:
};

}  // namespace uking::action
