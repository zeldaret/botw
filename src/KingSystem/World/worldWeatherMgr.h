#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

struct ClimateWeathers {
    s32 weather[20];
    // int _4[20];
};

// TODO
class WeatherMgr : public Job {
public:
    WeatherMgr();

    JobType getType() const override { return JobType::Weather; }

    void reset();
    void onUnload();
    void rerollClimateWindPowers();

    static bool isExposureZero();
    void loadInfo();
    WeatherType rollNewWeather(Climate climate);
    bool x_0();

    u8 _20[0x24 - 0x20];
    float _24;
    u8 weather;
    u8 _29;
    WeatherType _2a[20 * 18];
    u8 _193;
    struct ClimateWeathers climateWeathers[3];  // 0x194
    u8 _284[0x318 - 0x284];
    float mTimeBlock;  // 0x318
    u32 mWeekDay;      // 0x31c
    u8 _31C[0x398 - 0x320];
};
KSYS_CHECK_SIZE_NX150(WeatherMgr, 0x398);

}  // namespace ksys::world
