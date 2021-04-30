#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class TimeMgr : public Job {
public:
    TimeMgr();

    JobType getType() const override { return JobType::Time; }

    u8 _20[0x158 - 0x20];
};
KSYS_CHECK_SIZE_NX150(TimeMgr, 0x158);

}  // namespace ksys::world
