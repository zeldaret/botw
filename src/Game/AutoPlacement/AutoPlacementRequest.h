#pragma once
#include <prim/seadDelegate.h>
#include "KingSystem/Utils/Types.h"
namespace ksys::act {
class Actor;
}
namespace uking {
class AutoPlacement;
// Inferred owner name. The original manager stores 300 records of this type.
struct AutoPlacementRequest {
    AutoPlacementRequest() : mDelegate(this, &AutoPlacementRequest::onActorEvent) {}
    void onActorEvent(ksys::act::Actor* actor, s32 event);
    ksys::act::Actor* mActor = nullptr;
    AutoPlacement* mPlacement = nullptr;
    s32 mPlacementGeneration = 0;
    s16 mGroupIndex = 0;
    sead::Delegate2<AutoPlacementRequest, ksys::act::Actor*, s32> mDelegate;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementRequest, 0x38);
}  // namespace uking
