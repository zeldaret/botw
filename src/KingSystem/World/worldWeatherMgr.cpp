#include "KingSystem/World/worldWeatherMgr.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

WeatherType WeatherMgr::rollNewWeather(Climate climate) {
    auto* wm = Manager::instance();
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

    auto* env_mgr = wm->getEnvMgr();
    bool isWaterRelicRainOn = env_mgr->isWaterRelicRainOn(climate);
    if (isWaterRelicRainOn)
        weather = WeatherType::Bluesky;

    bool plateau_done = false;
    bool has_paraglider = false;
    auto gliderHandle = Manager::instance()->getTimeMgr()->isGetPlayerStole2Flag();
    if (gliderHandle != gdt::InvalidHandle) {
        gdt::Manager::instance()->getBool(gliderHandle, &plateau_done, true);
        has_paraglider = plateau_done;
    }

    if (has_paraglider || weather == WeatherType::Bluesky || weather == WeatherType::Cloudy)
        return weather;
    return WeatherType::Bluesky;
}
}  // namespace ksys::world
