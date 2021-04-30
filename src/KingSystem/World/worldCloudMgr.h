#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class CloudMgr : public Job {
public:
    CloudMgr();

    JobType getType() const override { return JobType::Cloud; }

    u8 _20[0x3fb8 - 0x20];
};
KSYS_CHECK_SIZE_NX150(CloudMgr, 0x3fb8);

}  // namespace ksys::world
