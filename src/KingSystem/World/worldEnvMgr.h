#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class EnvMgr : public Job {
public:
    EnvMgr();

    JobType getType() const override { return JobType::Env; }

    void resetForStageUnload();

    bool checkConcentrationDarkness() const;
    bool isBloodMoonNight() const;

    u8 _20[0x6b618 - 0x20];
};
KSYS_CHECK_SIZE_NX150(EnvMgr, 0x6b618);

}  // namespace ksys::world
