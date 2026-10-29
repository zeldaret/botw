#include "KingSystem/World/worldTempMgr.h"

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "random/seadGlobalRandom.h"

namespace ksys::world {
float getWeatherTemperatureOffset(WeatherType weather) {
    switch (weather) {
    case WeatherType::Bluesky:
        return 0.0f;
    case WeatherType::Cloudy:
        return -1.5f;
    case WeatherType::Rain:
        return -3.0f;
    case WeatherType::HeavyRain:
        return -3.0f;
    case WeatherType::Snow:
        return -3.0f;
    case WeatherType::HeavySnow:
        return -3.0f;
    case WeatherType::ThunderStorm:
        return -1.5f;
    default:
        return -3.0f;
    }
}

f32 blend_value(f32 a, f32 b, f32 t) {
    return a * t + b * (1.0f - t);
}

float calc_step(float value, float step, float target) {
    if (target >= 0.0f) {
        if (value + step <= target) {
            return step;
        }

        if (value < target) {
            return target - value;
        }
    } else {
        if (value + step >= target) {
            return step;
        }

        if (value > target) {
            return target - value;
        }
    }

    return 0.0f;
}

TempMgr::TempMgr() {
    loadInfo();
}

TempMgr::~TempMgr() = default;

void TempMgr::x() {
    _7c = 2;
    _80 = 0.2f;
}

void TempMgr::loadInfo() {
    _38 = 0;
    _3c = 23.0f;
    _40 = 23.0f;
    _44 = 23.0f;
    _20 = 23.0f;
    _24.value = 23.0f;
    _24.prev_value = 23.0f;
    mStepValue = 0.4f;
    mTempMax = 50.0f;
    mTempMin = -50.0f;
    mCurrentHour = -1;
    mCurrentClimate = Climate(-1);
    mMoisture = 0.0f;
    _74 = 0.0f;
    _78 = 0.0f;
    _7c = 0.0f;
    mWeatherOffset = 0.0f;
    mPlayerElevation = 0.0f;
    _60 = 0.0f;
    mSpeedupTimer = 0;
    _80 = 0.2f;
    _84 = 1.0f;
    _88 = 1.0f;
}

float TempMgr::calcTemperature() {
    mPlayerElevation = Manager::instance()->getPlayerPos().y;
    float day = Manager::instance()->calcTempDay(mPlayerElevation);
    float night = Manager::instance()->calcTempNight(mPlayerElevation);

    // Lerp between day and night temperature: 0.0 is day. 1.0 is night
    float current_day_time = Manager::instance()->getTimeMgr()->getTemperatureMultiplier();
    float temperature = sead::lerp(day, night, current_day_time);

    // If the temperature is set, we should just return it blindly
    // but if not, we calculate how weather affects the temperature
    if (!Manager::instance()->isTemperatureSet()) {
        WeatherType weather = Manager::instance()->getWeatherMgr()->getWeather();
        WeatherType weather2 = Manager::instance()->getWeatherMgr()->getWeather2();

        float currentWeatherRate = Manager::instance()->getWeatherMgr()->_24;
        float startTemp = getWeatherTemperatureOffset(weather);
        float endTemp = getWeatherTemperatureOffset(weather2);

        // Blend between the weather types
        mWeatherOffset = blend_value(startTemp, endTemp, currentWeatherRate);
        return temperature + mWeatherOffset;
    }

    mWeatherOffset = 0.0f;
    return temperature;
}

void TempMgr::calc1() {
    float temp = calcTemperature();

    auto& v = _24;
    float step = getStepValue();

    v.chase(temp, step);
    v.updateStats();
    _20 = v.value;

    _60 = 0.0f;

    float offset = 0.0f;

    // 49.9 and -9.9 are the hottest and coldest temperatures (in degrees C) at 0 elevation
    switch (Manager::instance()->getTemp798()) {
    case 1:
        _60 = 49.9f;
        offset = calc_step(_24.value, mTempMax, 49.9f);
        break;
    case 2:
        _60 = -9.9f;
        offset = calc_step(_24.value, mTempMin, -9.9f);
        break;
    default:
        break;
    }

    _40 = _44;
    _20 = offset + v.value;
    _3c = offset + v.value;
}

void TempMgr::calc_() {
    if (Manager::instance()->worldInfoIsLoaded()) {
        calc1();
        calc2();
    }

    // If the player teleported, we want the temperature to change rapidly
    if (Manager::instance()->hasCameraOrPlayerMoved(20.0f))
        mSpeedupTimer = 10;

    if (mSpeedupTimer != 0)
        mSpeedupTimer--;
}


void TempMgr::calc2() {
    int hour = Manager::instance()->getTimeMgr()->getHour();
    Climate climate = Manager::instance()->getCurrentClimate();

    if (mCurrentClimate != climate) {
        mMoisture = calcRandomMoisture();
        mCurrentClimate = climate;
    }

    if (mCurrentHour != hour) {
        mMoisture = calcRandomMoisture();
        mCurrentHour = hour;
    }

    WeatherType weather = Manager::instance()->getWeatherMgr()->getWeather();
    if (Manager::instance()->getWeatherMgr()->_24 < 0.9f) {
        float moisture = sead::Mathf::clampMax(mMoisture, 100.0f);
        if (_74 > 0.0f)
            moisture += _78;
    } else {
        switch (weather) {
        case WeatherType::Cloudy: case WeatherType::ThunderStorm:
            break;
        case WeatherType::Rain:

            break;
        case WeatherType::Snow:
            break;
        }
    }
}

float TempMgr::getStepValue() const {
    float step = mStepValue;

    // If the player teleported, the temperature was set etc., we want to take BIG steps towards the target
    if (mSpeedupTimer != 0 || Manager::instance()->getTempTimer() != 0) {
        step = 100.0f;
    }

    return step;
}

void TempMgr::setInstantTemperature() {
    mSpeedupTimer = 8;
}

float TempMgr::calcRandomMoisture() {
    float random = sead::GlobalRandom::instance()->getF32();
    int hour = Manager::instance()->getTimeMgr()->getHour();

    float t = random;

    // On average higher fog between 5-9am if the fogtype isn't 1
    if (Manager::instance()->getFogType() != 1 && hour >= 5 && hour <= 9) {
        t = random * 0.5f + 0.5f;
    }

    float max = Manager::instance()->getMoistureMax();
    float min = Manager::instance()->getMoistureMin();
    return sead::lerp(min, max, t);
}
}  // namespace ksys::world
