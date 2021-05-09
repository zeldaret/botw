#include "KingSystem/World/worldManager.h"
#include <cmath>
#include <container/seadSafeArray.h>
#include <math/seadMathCalcCommon.h>
#include <mc/seadWorkerMgr.h>
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Resource/resLoadRequest.h"
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

void Manager::unload() {
    mStageType = {};
    mWorldInfoLoadStatus = WorldInfoLoadStatus::Unloaded;
    mDungeonEnv.mResHandle.requestUnload2();
    getWeatherMgr()->onUnload();
}

// NON_MATCHING: stores in a different order (handwritten assignments?) but should be equivalent
Manager::Manager() = default;

static Job* makeJob(JobType type, sead::Heap* heap) {
    switch (type) {
    case JobType::Time:
        return new (heap) TimeMgr;
    case JobType::Sky:
        return new (heap) SkyMgr;
    case JobType::ShootingStar:
        return new (heap) ShootingStarMgrEx;
    case JobType::Weather:
        return new (heap) WeatherMgr;
    case JobType::Temp:
        return new (heap) TempMgr;
    case JobType::Wind:
        return new (heap) WindMgr;
    case JobType::Env:
        return new (heap) EnvMgr;
    case JobType::Dof:
        return new (heap) DofMgr;
    case JobType::Chemical:
        return new (heap) ChemicalMgr;
    }
    return nullptr;
}

void Manager::init(sead::Heap* heap) {
    mMgrs.allocBuffer(NumJobTypes, heap);
    mAtomicPtrArray.allocBuffer(0x1000, heap);
    mAtomicPtrArray.clear();

    mJobQueue.initialize(NumJobTypes, heap);
    mJobQueue.clear();

    mWorldInfo.mClimates.allocBufferAssert(NumClimates, heap);

    for (int i = 0; i < NumJobTypes; ++i) {
        auto* job = makeJob(JobType(i), heap);
        if (job) {
            job->init(heap);
            mMgrs.pushBack(job);
        }
    }

    mWorldInfoLoadStatus = WorldInfoLoadStatus::NotLoaded;
}

void Manager::resetForStageUnload() {
    getTimeMgr()->resetForStageUnload();
    getSkyMgr()->resetForStageUnload();
}

void Manager::loadWorldInfoRes() {
    res::LoadRequest req(0x2000, 1, false);
    req.mRequester = "wiWorldMgr";
    mInfoRes = mWorldInfo.mResHandle.load("WorldMgr/normal.bwinfo", &req);
}

void Manager::updateRemainsType() {
    if (StageInfo::getCurrentMapName().include("RemainsWind")) {
        mRemainsType = RemainsType::Wind;
    } else if (StageInfo::getCurrentMapName().include("RemainsElectric")) {
        mRemainsType = RemainsType::Electric;
    } else if (StageInfo::getCurrentMapName().include("RemainsFire")) {
        mRemainsType = RemainsType::Fire;
    } else if (StageInfo::getCurrentMapName().include("RemainsWater")) {
        mRemainsType = RemainsType::Water;
    } else if (StageInfo::getCurrentMapName().include("FinalTrial")) {
        mRemainsType = RemainsType::FinalTrial;
    }
}

Manager::~Manager() {
    for (auto& mgr : mMgrs)
        delete &mgr;

    mMgrs.freeBuffer();
    mAtomicPtrArray.freeBuffer();
    mWorldInfo.mClimates.freeBuffer();
}

void Manager::initBeforeStageGen() {
    getChemicalMgr()->initBeforeStageGen();
}

void Manager::unload2() {
    getChemicalMgr()->unload2();
}

void Manager::clearArray() {
    mAtomicPtrArray.clear();
}

int Manager::getWeatherBlueskyRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].weatherBlueskyRate.ref();
}

int Manager::getWeatherCloudyRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].weatherCloudyRate.ref();
}

int Manager::getWeatherRainRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].weatherRainRate.ref();
}

int Manager::getWeatherHeavyRainRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].weatherHeavyRainRate.ref();
}

int Manager::getWeatherStormRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].weatherStormRate.ref();
}

void Manager::calcManagers(sead::WorkerMgr* worker_mgr) {
    if (_5e0.isOffBit(0))
        worker_mgr = nullptr;

    sead::CoreIdMask cores{sead::CoreId::cMain, sead::CoreId::cSub1, sead::CoreId::cSub2};
    mJobQueue.clear();
    if (worker_mgr) {
        for (auto& mgr : mMgrs)
            mJobQueue.enque(&mgr);

        worker_mgr->pushJobQueue("calc", &mJobQueue, cores, sead::SyncType::cNoSync,
                                 sead::JobQueuePushType::cForward);
    } else {
        for (auto& mgr : mMgrs)
            mgr.invoke();
    }
}

void Manager::changeWind(int direction, bool enable_auto_wind, float speed) {
    mManualWindTimer = 10;
    mWindDirectionType = direction;
    mManualWindSpeed = speed;
    mEnableAutoWind = enable_auto_wind;
}

void Manager::setManualWind(bool enable_auto_wind, sead::Vector3f dir, float speed) {
    mManualWindTimer = 10;
    mWindDirectionType = -1;
    mWindDir = dir;
    mManualWindSpeed = speed;
    mEnableAutoWind = enable_auto_wind;
}

void Manager::resetManualWind() {
    if (mManualWindTimer <= 1)
        mManualWindTimer = 0;
}

void Manager::setDirectionalLight(float angle_x, float angle_y) {
    const auto x_rad = sead::Mathf::deg2rad(angle_x);
    const auto y_rad = sead::Mathf::deg2rad(angle_y);

    mDirectionalLightVecA.x = std::cos(x_rad) * std::sin(y_rad);
    mDirectionalLightVecA.y = std::sin(x_rad);
    mDirectionalLightVecA.z = std::cos(x_rad) * std::cos(y_rad);
    mDirectionalLightVecB = mDirectionalLightVecA;
    mDirectionalLightTimer = 1;
}

bool Manager::isGerudoDesertClimate() const {
    if (mCurrentClimate != Climate::GerudoDesertClimate &&
        mCurrentClimate != Climate::GerudoDesertClimateLv2) {
        return false;
    }
    return true;
}

bool Manager::hasCameraOrPlayerMoved(float distance_threshold) const {
    const auto camera_dist = sead::norm2(mCameraPos - mPrevCameraPos);
    const auto player_dist = sead::norm2(mPlayerPos - mPrevPlayerPos);
    const bool moved = player_dist >= distance_threshold || camera_dist >= distance_threshold;

    if (sead::norm2(mPlayerPos - mPrevPlayerPos) <= 100.0 &&
        evt::Manager::instance()->hasActiveEvent()) {
        return false;
    }

    return moved;
}

int Manager::getDungeonSize() const {
    for (int i = 0; i < DungeonSize::size(); ++i) {
        if (mDungeonEnv.mDungeonSize.ref() == DungeonSize::text(i))
            return DungeonSize(i);
    }
    return DungeonSize::XL;
}

int Manager::getDungeonType() const {
    for (int i = 0; i < DungeonType::size(); ++i) {
        if (mDungeonEnv.mDungeonType.ref() == DungeonType::text(i))
            return DungeonType(i);
    }
    return DungeonType::Gimmick;
}

float Manager::getDungeonLightLongitude() const {
    return mDungeonEnv.mLightLongitude.ref();
}

void Manager::setCameraDistForRemainsElectric(sead::Vector3f pos) {
    _7ac = 10;
    _770 = sead::norm2(mCameraPos - pos);
}

void Manager::setFocusDist(float dist) {
    _720 = 2;
    _7b8 = 2;
    mFocusDist = dist;
}

void Manager::rerollClimateWindPowers() {
    getWeatherMgr()->rerollClimateWindPowers();
}

void Manager::forceResetManualWind() {
    mManualWindTimer = 0;
}

void Manager::setTemperatureDay(float temp) {
    /// @bug this should be a strict inequality (<), not <=
    if (mTempDirectDay <= 99999) {
        if (temp > 0.0) {
            if (mTempDirectDay > temp)
                return;
        } else {
            if (mTempDirectDay < temp)
                return;
        }
    }

    mTempDirectDay = temp;
    mTempDirectDayTimer = 4;
}

void Manager::setTemperatureNight(float temp) {
    /// @bug this should be a strict inequality (<), not <=
    if (mTempDirectNight <= 99999) {
        if (temp > 0.0) {
            if (mTempDirectNight > temp)
                return;
        } else {
            if (mTempDirectNight < temp)
                return;
        }
    }

    mTempDirectNight = temp;
    mTempDirectNightTimer = 4;
}

// NON_MATCHING: mPlayerPos.y gets loaded into s8 instead of w20
void Manager::setIgnitedLevel(int level, float radius, sead::Vector3f center) {
    mIgnitedTimer = 4;
    mIgnitedRadius = radius;
    mIgnitedCenter = center;
    const sead::Vector3f unk_center{-2004, mPlayerPos.y, 1710};
    mIgnitedLevel = level;

    if (sead::norm2(mPlayerPos - unk_center) < 20.0) {
        mIgnitedCenter = unk_center;
        mIgnitedRadius = 7.0;
    }
}

}  // namespace ksys::world
