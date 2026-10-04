#pragma once

#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

constexpr u32 NumWeatherCycles = 3;

// This may be incorrect
struct ClimateWeathers {
    s32 weather[NumWeatherCycles];
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
    WeatherType getWeather() const;
    WeatherType getWeatherForTimeBlock0(Climate climate) const;
    WeatherType getWeatherForTimeBlock1(Climate climate) const;
    WeatherType getWeatherForTimeBlock2(Climate climate) const;
    WeatherType getWeatherForTimeBlock3(Climate climate) const;
    WeatherType getWeatherForTimeBlock4(Climate climate) const;
    WeatherType getWeatherForTimeBlock5(Climate climate) const;
    bool isGetPlayerStole2() const;

    u8 _20[0x24 - 0x20];
    float _24;
    // Unsure of the type / variable
    u8 weather;
    u8 _29;
    WeatherType _2a[NumClimates * NumWeatherCycles * 6];
    u8 _193;
    ClimateWeathers mClimateWeathers[NumClimates];  // 0x194
    u8 _284[0x318 - 0x284];
    float mTimeBlock;  // 0x318
    u32 mWeekDay;      // 0x31c
    u8 _31c[0x393 - 0x320];
    u8 mBlueskyRain;
    u8 _394[0x398 - 0x394];
};
KSYS_CHECK_SIZE_NX150(WeatherMgr, 0x398);

}  // namespace ksys::world
