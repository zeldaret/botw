#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class SkyMgr : public Job {
public:
    SkyMgr();

    JobType getType() const override { return JobType::Sky; }

    void onTimeUpdate();

    u8 _20[0x3fb8 - 0x20];
};
KSYS_CHECK_SIZE_NX150(SkyMgr, 0x3fb8);

}  // namespace ksys::world
