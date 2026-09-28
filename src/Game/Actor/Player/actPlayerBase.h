#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// TODO
class PlayerBase : public ksys::act::Actor {
public:
    // FIXME: name for x and name+type for y
    void switchEquipment(const sead::SafeString& slot, int frames, int x = -1,
                         const uintptr_t& y = {});

    // FIXME: name for x
    void setExtraLife(s32 extra_life, f32 x);
};

}  // namespace uking::act
