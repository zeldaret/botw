#pragma once

#include "Game/AI/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaObserveActorAction : public AreaActorObserve {
    SEAD_RTTI_OVERRIDE(AreaObserveActorAction, AreaActorObserve)
public:
    explicit AreaObserveActorAction(const InitArg& arg);
    ~AreaObserveActorAction() override;

protected:
};

}  // namespace uking::action
