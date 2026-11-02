#include "KingSystem/World/worldTempMgr.h"

#include <random/seadGlobalRandom.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"

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

float calcExtremeOffset(float base, float maxOffset, float targetExtreme) {
    if (targetExtreme >= 0.0f) {
        if (base + maxOffset <= targetExtreme) {
            return maxOffset;
        }

        if (base < targetExtreme) {
            return targetExtreme - base;
        }
    } else {
        if (base + maxOffset >= targetExtreme) {
            return maxOffset;
        }

        if (base > targetExtreme) {
            return targetExtreme - base;
        }
    }

    return 0.0f;
}

TempMgr::TempMgr() {
    reset();
}

void TempMgr::reset() {
    mHumidity = 0.0f;
    mTemperature = 23.0f;
    _40 = 23.0f;
    _44 = 23.0f;
    mTemperature2 = 23.0f;
    mVFRTemperature.value = 23.0f;
    mVFRTemperature.prev_value = 23.0f;
    mStepValue = 0.4f;
    mTempAddValue = 50.0f;
    mTempAddEnd = -50.0f;
    mCurrentHour = -1;
    mCurrentClimate = Climate(-1);
    mMoisture = 0.0f;
    _74 = 0.0f;
    _78 = 0.0f;
    _7c = 0;
    mWeatherOffset = 0.0f;
    mPlayerElevation = 0.0f;
    mTempExtreme = 0.0f;
    mSpeedupTimer = 0;
    _80 = 0.2f;
    mBloomThreshold = 1.0f;
    mBloomIntensity = 1.0f;
}

TempMgr::~TempMgr() = default;

void TempMgr::init_(sead::Heap* heap) {}

float TempMgr::calcTemperature() {
    mPlayerElevation = Manager::instance()->getPlayerPos().y;
    float day_temp = Manager::instance()->calcTempDay(mPlayerElevation);
    float night_temp = Manager::instance()->calcTempNight(mPlayerElevation);

    // Lerp between day and night temperature: 0.0 is day. 1.0 is night
    float current_day_time = Manager::instance()->getTimeMgr()->getTemperatureMultiplier();
    float temperature = sead::lerp(day_temp, night_temp, current_day_time);

    // If the temperature is set, we should just return it blindly
    // but if not, we calculate how weather affects the temperature
    if (!Manager::instance()->isTemperatureSet()) {
        WeatherType weather = Manager::instance()->getWeatherMgr()->getWeather();
        WeatherType weather2 = Manager::instance()->getWeatherMgr()->getWeather2();

        float currentWeatherRate = Manager::instance()->getWeatherMgr()->_24;
        float startTemp = getWeatherTemperatureOffset(weather);
        float endTemp = getWeatherTemperatureOffset(weather2);

        // Blend between the weather types
        mWeatherOffset = currentWeatherRate * startTemp + (1.0f - currentWeatherRate) * endTemp;
        return temperature + mWeatherOffset;
    }

    mWeatherOffset = 0.0f;
    return temperature;
}

float TempMgr::calcRandomMoisture() {
    float random = sead::GlobalRandom::instance()->getF32();
    int hour = Manager::instance()->getTimeMgr()->getHour();

    float t = random;

    // On average higher moisture between 5-9am if the fogtype isn't 1
    if (Manager::instance()->getFogType() != 1 && hour >= 5 && hour <= 9) {
        t = random * 0.5f + 0.5f;
    }

    float max = Manager::instance()->getMoistureMax();
    float min = Manager::instance()->getMoistureMin();
    return sead::lerp(min, max, t);
}

void TempMgr::calcType1_() {
    float temp = calcTemperature();

    auto& vfr = mVFRTemperature;
    const float step = getStepValue();

    mVFRTemperature.chase(temp, step);
    mVFRTemperature.updateStats();
    mTemperature2 = mVFRTemperature.value;

    mTempExtreme = 0.0f;

    float offset = 0.0f;

    switch (Manager::instance()->getTempExtreme()) {
    case Manager::TemperatureExtreme::Hot:
        mTempExtreme = 49.9f;
        offset = calcExtremeOffset(mVFRTemperature.value, mTempAddValue, 49.9f);
        break;
    case Manager::TemperatureExtreme::Cold:
        mTempExtreme = -9.9f;
        offset = calcExtremeOffset(mVFRTemperature.value, mTempAddEnd, -9.9f);
        break;
    default:
        break;
    }

    _40 = _44;
    mTemperature2 = offset + vfr.value;
    mTemperature = offset + vfr.value;
}

float TempMgr::getStepValue() const {
    float step = mStepValue;

    // If the player teleported, the temperature was set etc., we want to take BIG steps towards the
    // target
    if (mSpeedupTimer != 0 || Manager::instance()->getTempTimer() != 0) {
        step = 100.0f;
    }

    return step;
}

void TempMgr::calc_() {
    if (Manager::instance()->worldInfoIsLoaded()) {
        TempMgr::calcType1_();  // Must be called as TempMgr:: to skip vtable lookup
        TempMgr::calcType2_();
    }

    // If the player teleported, we want the temperature to change rapidly
    if (Manager::instance()->hasCameraOrPlayerMoved(20.0f))
        mSpeedupTimer = 10;

    if (mSpeedupTimer != 0)
        mSpeedupTimer--;
}

void TempMgr::setInstantTemperature() {
    mSpeedupTimer = 8;
}

void TempMgr::x() {
    _7c = 2;
    _80 = 0.2f;
}

void TempMgr::m8_null() {
    // Probably a debug function. Totally empty in exefs binary.
}
}  // namespace ksys::world
