#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class SkyMgr : public Job {
public:
    SkyMgr();

    JobType getType() const override { return JobType::Sky; }

    void resetForStageUnload();

    bool checkConcentrationDarkness() const;

    u8 _20[0x6b618 - 0x20];
};
KSYS_CHECK_SIZE_NX150(SkyMgr, 0x6b618);

}  // namespace ksys::world
