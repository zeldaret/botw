#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class DofMgr : public Job {
public:
    DofMgr();

    JobType getType() const override { return JobType::Dof; }

    u8 _20[0x1c0 - 0x20];
};
KSYS_CHECK_SIZE_NX150(DofMgr, 0x1c0);

}  // namespace ksys::world
