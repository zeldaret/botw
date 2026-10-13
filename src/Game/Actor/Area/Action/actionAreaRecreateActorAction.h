#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaRecreateActorAction : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaRecreateActorAction, AreaActionBase)
public:
    explicit AreaRecreateActorAction(const InitArg& arg);
    ~AreaRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::action
