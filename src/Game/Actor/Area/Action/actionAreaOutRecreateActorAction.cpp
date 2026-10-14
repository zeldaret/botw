#include "Game/Actor/Area/Action/actionAreaOutRecreateActorAction.h"

namespace uking::action {

AreaOutRecreateActorAction::AreaOutRecreateActorAction(const InitArg& arg) : AreaActionBase(arg) {}

AreaOutRecreateActorAction::~AreaOutRecreateActorAction() = default;

bool AreaOutRecreateActorAction::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

}  // namespace uking::action
