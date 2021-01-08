#pragma once

#include <prim/seadSafeString.h>

namespace ksys::act {

// TODO
class PlayerBase {
public:
    // FIXME: name for x and name+type for y
    void switchEquipment(const sead::SafeString& slot, int frames, int x = -1,
                         const uintptr_t& y = {});
};

}  // namespace ksys::act
