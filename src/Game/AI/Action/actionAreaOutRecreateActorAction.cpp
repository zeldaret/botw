#include "Game/AI/Action/actionAreaOutRecreateActorAction.h"

namespace uking::action {

AreaOutRecreateActorAction::AreaOutRecreateActorAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaOutRecreateActorAction::~AreaOutRecreateActorAction() = default;

bool AreaOutRecreateActorAction::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

}  // namespace uking::action
