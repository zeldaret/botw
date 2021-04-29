#include "KingSystem/World/worldManager.h"
#include <container/seadSafeArray.h>
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::world {

namespace {

util::InitConstants sInitConsts;

const sead::SafeString cWeatherTypes[] = {
    "Bluesky",   "Cloudy",       "Rain",        "HeavyRain",   "Snow",
    "HeavySnow", "ThunderStorm", "ThunderRain", "BlueskyRain",
};

const sead::SafeString cMagicStrings[] = {
    "MagicStorm,MagicRedhot,MagicCold",
    {},
    {},
};

const sead::SafeString cClimates[] = {
    "HyrulePlainClimate",
    "NorthHyrulePlainClimate",
    "HebraFrostClimate",
    "TabantaAridClimate",
    "FrostClimate",
    "GerudoDesertClimate",
    "GerudoPlateauClimate",
    "EldinClimateLv0",
    "TamourPlainClimate",
    "ZoraTemperateClimate",
    "HateruPlainClimate",
    "FiloneSubtropicalClimate",
    "SouthHateruHumidTemperateClimate",
    "EldinClimateLv1",
    "EldinClimateLv2",
    // sic
    "DarkWoodsClimat",
    "LostWoodClimate",
    "GerudoFrostClimate",
    "KorogForest",
    "GerudoDesertClimateLv2",
};

bool isValidTemp(float temp) {
    return temp < 99999;
}

}  // namespace

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

WeatherType Manager::getWeatherType() const {
    return mWeatherType;
}

void Manager::setWeatherType(WeatherType weather_type, bool x, bool y, bool for_demo) {
    // Ignore invalid weather requests.
    if (u32(weather_type) >= NumWeatherTypes)
        return;

    if (mWeatherSetForDemo && !for_demo)
        return;

    if (_794 != 0 && y && mWeatherType.mValue > u8(weather_type))
        return;

    mWeatherType = weather_type;
    _794 = 4;
    _7d5 = x;
    mWeatherSetForDemo = for_demo;
}

void Manager::setWeatherType(const sead::SafeString& weather_type, bool x, bool y, bool for_demo) {
    for (u8 i = 0; i < NumWeatherTypes; ++i) {
        if (weather_type == cWeatherTypes[i]) {
            setWeatherType(WeatherType(i), x, y, for_demo);
            return;
        }
    }
}

const char* Manager::getWeatherTypeString(WeatherType type) {
    auto index = ptrdiff_t(type);
    if (u32(index) >= NumWeatherTypes)
        index = 0;
    return cWeatherTypes[index].cstr();
}

Climate Manager::getClimate(const sead::Vector3f& pos) const {
    const auto area = eco::Ecosystem::instance()->getFieldMapArea(pos.x, pos.z);
    if (area < 0)
        return {};

    const char* climate;
    eco::Ecosystem::instance()->getClimateNameByNum(area, &climate);
    if (climate == nullptr)
        return {};

    for (int i = 0; i < int(NumClimates); ++i) {
        if (cClimates[i] == climate)
            return Climate(i);
    }
    return {};
}

Climate Manager::getCurrentClimate() const {
    return mCurrentClimate;
}

Climate Manager::getPrevClimate() const {
    return mPrevClimate;
}

float Manager::getClimateTransitionProgress() const {
    return mClimateTransitionProgress;
}

bool Manager::isDayLockBlueSky(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].dayLockBlueSky.ref();
}

bool Manager::isNightLockBlueSky(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].nightLockBlueSky.ref();
}

float Manager::calcTempDay(float height) const {
    float normal_temp = 23.0f;

    if (isMainField() && worldInfoLoaded()) {
        height = sead::Mathf::max(height, 0.0f);

        int a = -1;
        float h{};
        for (int i = 0; i < ClimateInfo::NumClimateTemp; ++i) {
            h = float(ClimateInfo::NumClimateTemp - (i + 1)) * 100.0f;
            if (height >= h) {
                a = i;
                break;
            }
        }

        float t = 1.0f;
        int b = a;
        if (a > 0) {
            b = a - 1;
            t = 1.0f - (h + 100.0f - height) / (h + 100.0f - h);
        }

        if (a != -1) {
            const auto& temps = mWorldInfo.mClimates[int(mCurrentClimate)].climateTempDay;
            const float v = *temps[b];
            const float u = *temps[a];
            normal_temp = u + t * (v - u);
        }
    }

    float temp = mTempDirectDay;
    if (!isValidTemp(temp))
        temp = normal_temp;

    const float extra_temp = mTempDirectDayExtra;
    if (isValidTemp(extra_temp))
        temp += extra_temp;

    return temp;
}

float Manager::calcTempNight(float height) const {
    float normal_temp = 23.0f;

    if (isMainField() && worldInfoLoaded()) {
        height = sead::Mathf::max(height, 0.0f);

        int a = -1;
        float h{};
        for (int i = 0; i < ClimateInfo::NumClimateTemp; ++i) {
            h = float(ClimateInfo::NumClimateTemp - (i + 1)) * 100.0f;
            if (height >= h) {
                a = i;
                break;
            }
        }

        float t = 1.0f;
        int b = a;
        if (a > 0) {
            b = a - 1;
            t = 1.0f - (h + 100.0f - height) / (h + 100.0f - h);
        }

        if (a != -1) {
            const auto& temps = mWorldInfo.mClimates[int(mCurrentClimate)].climateTempNight;
            const float v = *temps[b];
            const float u = *temps[a];
            normal_temp = u + t * (v - u);
        }
    }

    float temp = mTempDirectNight;
    if (!isValidTemp(temp))
        temp = normal_temp;

    const float extra_temp = mTempDirectNightExtra;
    if (isValidTemp(extra_temp))
        temp += extra_temp;

    return temp;
}

float Manager::getMoistureMax() const {
    if (!isMainField() || !worldInfoLoaded())
        return 0.0;
    return mWorldInfo.mClimates[int(mCurrentClimate)].moistureMax.ref();
}

float Manager::getMoistureMin() const {
    if (!isMainField() || !worldInfoLoaded())
        return 0.0;
    return mWorldInfo.mClimates[int(mCurrentClimate)].moistureMin.ref();
}

sead::Vector3f Manager::getWindDirection() const {
    float x;
    int idx = 0;
    if (mStageType == StageType::OpenWorld && mFieldType == FieldType::AocField &&
        mScalingMode == ScalingMode::Disabled) {
        x = std::sin(mWindDirections[0]);
    } else {
        x = std::sin(mWindDirections[int(mCurrentClimate)]);
        idx = int(mCurrentClimate);
    }
    return {x, 0, std::cos(mWindDirections[idx])};
}

float Manager::getWindSpeed() const {
    float value = 0.0;
    if (isMainField() && worldInfoLoaded()) {
        value = mWorldInfo.mClimates[int(mCurrentClimate)].windPower.ref();
        value *= mWorldInfo.mClimates[int(mCurrentClimate)].windPowerMultiplier;
    }
    overrideWindSpeed(&value);
    return value;
}

float Manager::getWindSpeed(const sead::Vector3f& pos) const {
    float value = 0.0;
    if (isMainField() && worldInfoLoaded()) {
        value = mWorldInfo.mClimates[int(getClimate(pos))].windPower.ref();
        value *= mWorldInfo.mClimates[int(getClimate(pos))].windPowerMultiplier;
    }
    overrideWindSpeed(&value);
    return value;
}

void Manager::overrideWindSpeed(float* wind_speed) const {
    if (isAocField())
        *wind_speed = mWindSpeedAocField;
    if (mMapEdgeWindEnabled)
        *wind_speed = mMapEdgeWindSpeed;
    if (mManualWindTimer != 0)
        *wind_speed = mManualWindSpeed;
}

sead::Vector3f Manager::getWindDirection(const sead::Vector3f& pos) const {
    float x = std::sin(mWindDirections[int(getClimate(pos))]);
    float z = std::cos(mWindDirections[int(getClimate(pos))]);
    return {x, 0, z};
}

int Manager::getPaletteSetSelect() const {
    if (!worldInfoLoaded() || mStageType != StageType::OpenWorld)
        return 0;

    const auto climate = mCurrentClimate;

    if (isAocField())
        return 0;

    return mWorldInfo.mClimates[int(climate)].paletteSetSelect.ref();
}

int Manager::getFogType() const {
    if (!worldInfoLoaded() || mStageType != StageType::OpenWorld)
        return 0;

    const auto climate = mCurrentClimate;

    if (isAocField())
        return 0;

    return mWorldInfo.mClimates[int(climate)].fogType.ref();
}

bool Manager::isForbidComeback() const {
    return isForbidComeback(mCurrentClimate);
}

bool Manager::isForbidComeback(Climate climate) const {
    if (!worldInfoLoaded() || !isMainField())
        return false;
    return mWorldInfo.mClimates[int(climate)].forbidComeback.ref();
}

// NON_MATCHING: stores in a different order (handwritten assignments?) but should be equivalent
Manager::Manager() = default;

}  // namespace ksys::world
