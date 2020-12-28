#pragma once

#include "Game/AI/Action/actionBackStepBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStep : public BackStepBase {
    SEAD_RTTI_OVERRIDE(BackStep, BackStepBase)
public:
    explicit BackStep(const InitArg& arg);

protected:
};

}  // namespace uking::action
