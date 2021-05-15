#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class TempMgr : public Job {
public:
    TempMgr();

    JobType getType() const override { return JobType::Temp; }

    void reset();

    u8 _20[0x90 - 0x20];
};
KSYS_CHECK_SIZE_NX150(TempMgr, 0x90);

}  // namespace ksys::world
