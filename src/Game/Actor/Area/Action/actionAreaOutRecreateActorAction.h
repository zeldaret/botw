#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaOutRecreateActorAction : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaOutRecreateActorAction, AreaActionBase)
public:
    explicit AreaOutRecreateActorAction(const InitArg& arg);
    ~AreaOutRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::action
