#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldShootingStarMgr.h"

namespace ksys::world {

// TODO
class ShootingStarMgrEx : public ShootingStarMgr {
public:
    ShootingStarMgrEx();

    u8 _30[0x88 - 0x30];
};
KSYS_CHECK_SIZE_NX150(ShootingStarMgrEx, 0x88);

}  // namespace ksys::world
