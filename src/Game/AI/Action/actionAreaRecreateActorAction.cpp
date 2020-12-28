#include "Game/AI/Action/actionAreaRecreateActorAction.h"

namespace uking::action {

AreaRecreateActorAction::AreaRecreateActorAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaRecreateActorAction::~AreaRecreateActorAction() = default;

bool AreaRecreateActorAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

}  // namespace uking::action
