#include "Game/AI/Action/actionAreaActorObserveByActorTag.h"

namespace uking::action {

AreaActorObserveByActorTag::AreaActorObserveByActorTag(const InitArg& arg)
    : AreaActorObserve(arg) {}

AreaActorObserveByActorTag::~AreaActorObserveByActorTag() = default;

bool AreaActorObserveByActorTag::init_(sead::Heap* heap) {
    return AreaActorObserve::init_(heap);
}

}  // namespace uking::action
