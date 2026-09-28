#include "Game/Actor/Area/Action/actionAreaRecreateActorAction.h"

namespace uking::action {

AreaRecreateActorAction::AreaRecreateActorAction(const InitArg& arg) : AreaActionBase(arg) {}

AreaRecreateActorAction::~AreaRecreateActorAction() = default;

bool AreaRecreateActorAction::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

}  // namespace uking::action
