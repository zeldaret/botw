#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaOutRecreateActorAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaOutRecreateActorAction, AreaTagAction)
public:
    explicit AreaOutRecreateActorAction(const InitArg& arg);
    ~AreaOutRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::action
