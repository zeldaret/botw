#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class WindMgr : public Job {
public:
    WindMgr();

    JobType getType() const override { return JobType::Wind; }

    u8 _20[0x138 - 0x20];
};
KSYS_CHECK_SIZE_NX150(WindMgr, 0x138);

}  // namespace ksys::world
