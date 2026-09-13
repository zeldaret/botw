#pragma once

#include "Game/Actor/Area/Action/actionAreaActorObserve.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActorObserveByActorTag : public AreaActorObserve {
    SEAD_RTTI_OVERRIDE(AreaActorObserveByActorTag, AreaActorObserve)
public:
    explicit AreaActorObserveByActorTag(const InitArg& arg);
    ~AreaActorObserveByActorTag() override;

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::action
