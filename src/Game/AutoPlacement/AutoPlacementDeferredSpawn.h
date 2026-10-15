#pragma once

#include "Game/AutoPlacement/AutoPlacement.h"

namespace ksys::act {
class Actor;
}

namespace uking {

struct DeferredActorSpawn {
    ksys::act::Actor* actor;
    sead::SafeString name;
    sead::Matrix34f transform;
    sead::Vector3f scale;
    u32 isBox;
    AutoPlacement placement;
    u16 count;
    bool active;
    bool started;
};
KSYS_CHECK_SIZE_NX150(DeferredActorSpawn, 0x8b68);

}  // namespace uking
