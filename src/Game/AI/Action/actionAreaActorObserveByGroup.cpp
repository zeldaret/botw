#include "Game/AI/Action/actionAreaActorObserveByGroup.h"

namespace uking::action {

AreaActorObserveByGroup::AreaActorObserveByGroup(const InitArg& arg) : AreaActorObserve(arg) {}

AreaActorObserveByGroup::~AreaActorObserveByGroup() = default;

bool AreaActorObserveByGroup::init_(sead::Heap* heap) {
    return AreaActorObserve::init_(heap);
}

}  // namespace uking::action
