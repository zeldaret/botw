#include "KingSystem/World/worldWeatherMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldManager.h"
namespace ksys::world {

WeatherType WeatherMgr::rollNewWeather(Climate climate) {
    auto wm = Manager::instance();
    int random = sead::GlobalRandom::instance()->getU32(99);
    WeatherType weather = [&] {
        const std::pair<WeatherType, int> rates[] = {
            {WeatherType::Bluesky, wm->getWeatherBlueskyRate(climate) - 1},
            {WeatherType::Cloudy, wm->getWeatherCloudyRate(climate)},
            {WeatherType::Rain, wm->getWeatherRainRate(climate)},
            {WeatherType::HeavyRain, wm->getWeatherHeavyRainRate(climate)},
        };
        for (auto [type, rate] : rates) {
            if (random <= rate)
                return type;
            random -= rate;
        }
        return WeatherType::ThunderRain;
    }();

    auto envMgr = wm->getEnvMgr();

    bool isWaterRelicRainOn = envMgr->isWaterRelicRainOn(climate);
    bool value = false;
    auto gliderHandle = Manager::instance()->getTimeMgr()->isGetPlayerStole2Flag();
    if (isWaterRelicRainOn)
        weather = WeatherType::Bluesky;
    bool hasParaglider = false;
    if (gliderHandle != gdt::InvalidHandle) {
        gdt::Manager::instance()->getBool(gliderHandle, &value, true);
        hasParaglider = value;
    } else {
        hasParaglider = false;
    }
    auto result = weather;
    if (weather == WeatherType::Bluesky || weather == WeatherType::Cloudy || hasParaglider)
        result = weather;
    else
        result = WeatherType::Bluesky;
    return result;
}
}  // namespace ksys::world
