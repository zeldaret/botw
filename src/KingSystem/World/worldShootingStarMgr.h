#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class ShootingStarMgr : public Job {
public:
    ShootingStarMgr();

    JobType getType() const override { return JobType::ShootingStar; }

    virtual void reset();

    u8 _20[0x30 - 0x20];
};
KSYS_CHECK_SIZE_NX150(ShootingStarMgr, 0x30);

}  // namespace ksys::world
