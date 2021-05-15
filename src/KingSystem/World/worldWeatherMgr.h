#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class WeatherMgr : public Job {
public:
    WeatherMgr();

    JobType getType() const override { return JobType::Weather; }

    void reset();
    void onUnload();
    void rerollClimateWindPowers();

    u8 _20[0x398 - 0x20];
};
KSYS_CHECK_SIZE_NX150(WeatherMgr, 0x398);

}  // namespace ksys::world
