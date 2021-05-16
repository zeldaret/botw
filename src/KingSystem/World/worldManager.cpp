#include "KingSystem/World/worldManager.h"
#include <cmath>
#include <container/seadSafeArray.h>
#include <gfx/seadCamera.h>
#include <math/seadMathCalcCommon.h>
#include <mc/seadWorkerMgr.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/System/CameraMgr.h"
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

    if (mWeatherTypeTimer != 0 && y && mWeatherType.mValue > u8(weather_type))
        return;

    mWeatherType = weather_type;
    mWeatherTypeTimer = 4;
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
    return mWorldInfo.mClimates[int(climate)].DayLockBlueSky.ref();
}

bool Manager::isNightLockBlueSky(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].NightLockBlueSky.ref();
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
            const auto& temps = mWorldInfo.mClimates[int(mCurrentClimate)].ClimateTempDay;
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
            const auto& temps = mWorldInfo.mClimates[int(mCurrentClimate)].ClimateTempNight;
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
    return mWorldInfo.mClimates[int(mCurrentClimate)].MoistureMax.ref();
}

float Manager::getMoistureMin() const {
    if (!isMainField() || !worldInfoLoaded())
        return 0.0;
    return mWorldInfo.mClimates[int(mCurrentClimate)].MoistureMin.ref();
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
        value = mWorldInfo.mClimates[int(mCurrentClimate)].WindPower.ref();
        value *= mWorldInfo.mClimates[int(mCurrentClimate)].WindPowerMultiplier;
    }
    overrideWindSpeed(&value);
    return value;
}

float Manager::getWindSpeed(const sead::Vector3f& pos) const {
    float value = 0.0;
    if (isMainField() && worldInfoLoaded()) {
        value = mWorldInfo.mClimates[int(getClimate(pos))].WindPower.ref();
        value *= mWorldInfo.mClimates[int(getClimate(pos))].WindPowerMultiplier;
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

    return mWorldInfo.mClimates[int(climate)].PaletteSetSelect.ref();
}

int Manager::getFogType() const {
    if (!worldInfoLoaded() || mStageType != StageType::OpenWorld)
        return 0;

    const auto climate = mCurrentClimate;

    if (isAocField())
        return 0;

    return mWorldInfo.mClimates[int(climate)].FogType.ref();
}

bool Manager::isForbidComeback() const {
    return isForbidComeback(mCurrentClimate);
}

bool Manager::isForbidComeback(Climate climate) const {
    if (!worldInfoLoaded() || !isMainField())
        return false;
    return mWorldInfo.mClimates[int(climate)].ForbidComeback.ref();
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
    getEnvMgr()->resetForStageUnload();
}

void Manager::loadWorldInfoRes() {
    res::LoadRequest req(0x2000, 1, false);
    req.mRequester = "wiWorldMgr";
    mInfoRes = mWorldInfo.mResHandle.load("WorldMgr/normal.bwinfo", &req);
}

void Manager::onStageInit(StageType stage_type, bool is_demo, bool is_main_field) {
    mTimer = 30;
    mTicks = 0;
    _6c8 = 0;
    _6cc = true;
    mStageType = mStageType2 = stage_type;
    mIsDemo = is_demo;
    mIsMainField = is_main_field;
    mIsBattleCurseR = false;
    mInFinalTrialBossBattleArea = false;

    if (auto* camera = CameraMgr::instance()->getLookAtCamera()) {
        mCameraPos = camera->getPos();
        mPrevCameraPos = mCameraPos;
        mPrevCameraPos.y += 200.0f;
        mCurrentClimate = getClimate(mCameraPos);
        act::ActorConstDataAccess accessor;
        act::ActorSystem::instance()->getPlayer(&accessor);
        if (accessor.hasProc()) {
            mPlayerPos = accessor.getPreviousPos();
            mPrevPlayerPos = mPlayerPos;
        }
        mPrevClimate = mCurrentClimate;
        mClimateTransitionProgress = 1.0f;
    }

    res::LoadRequest req(0x2000, 1, false);
    req.mRequester = "wiWorldMgr";
    if (mInfoRes) {
        auto* res = sead::DynamicCast<sead::DirectResource>(mInfoRes);
        if (!worldInfoLoaded()) {
            auto& climates = mWorldInfo.mClimates;
            for (int i = 0; i < climates.size(); ++i) {
                climates[i].WeatherType.init(0, "WeatherType", "天候状態 0:晴 1:曇 2:雨 3:雪",
                                             "Min=0, Max=10", &climates[i].obj);
                climates[i].WeatherBlueskyRate.init(60, "WeatherBlueskyRate", "晴天確率",
                                                    "Min=0, Max=60", &climates[i].obj);
                climates[i].WeatherCloudyRate.init(20, "WeatherCloudyRate", "曇天確率",
                                                   "Min=0, Max=20", &climates[i].obj);
                climates[i].WeatherRainRate.init(15, "WeatherRainRate", "雨天確率", "Min=0, Max=20",
                                                 &climates[i].obj);
                climates[i].WeatherHeavyRainRate.init(5, "WeatherHeavyRainRate", "大雨確率",
                                                      "Min=0, Max=20", &climates[i].obj);
                climates[i].WeatherStormRate.init(0, "WeatherStormRate", "嵐天確率",
                                                  "Min=0, Max=20", &climates[i].obj);
                climates[i].DayLockBlueSky.init(false, "DayLockBlueSky", "昼間晴天固定",
                                                "Min=0, Max=1", &climates[i].obj);
                climates[i].NightLockBlueSky.init(false, "NightLockBlueSky", "夜間晴天固定",
                                                  "Min=0, Max=1", &climates[i].obj);
                climates[i].ClimateTempDay[0].init(-60.0f, "ClimateTemperatureDay_1000", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[1].init(-60.0f, "ClimateTemperatureDay_0900", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[2].init(-60.0f, "ClimateTemperatureDay_0800", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[3].init(-45.0f, "ClimateTemperatureDay_0700", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[4].init(-30.0f, "ClimateTemperatureDay_0600", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[5].init(-10.0f, "ClimateTemperatureDay_0500", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[6].init(0.0f, "ClimateTemperatureDay_0400", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[7].init(10.0f, "ClimateTemperatureDay_0300", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[8].init(20.0f, "ClimateTemperatureDay_0200", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[9].init(23.0f, "ClimateTemperatureDay_0100", "",
                                                   "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempDay[10].init(25.0f, "ClimateTemperatureDay_0000", "",
                                                    "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[0].init(-63.0f, "ClimateTemperatureNight_1000", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[1].init(-63.0f, "ClimateTemperatureNight_0900", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[2].init(-63.0f, "ClimateTemperatureNight_0800", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[3].init(-48.0f, "ClimateTemperatureNight_0700", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[4].init(-33.0f, "ClimateTemperatureNight_0600", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[5].init(-13.0f, "ClimateTemperatureNight_0500", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[6].init(-3.0f, "ClimateTemperatureNight_0400", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[7].init(7.0f, "ClimateTemperatureNight_0300", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[8].init(17.0f, "ClimateTemperatureNight_0200", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[9].init(20.0f, "ClimateTemperatureNight_0100", "",
                                                     "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].ClimateTempNight[10].init(23.0f, "ClimateTemperatureNight_0000", "",
                                                      "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].MoistureMax.init(0.0, "MoistureMax", "最高湿度", "Min=0.0f, Max=100.0f",
                                             &climates[i].obj);
                climates[i].MoistureMin.init(0.0, "MoistureMin", "最低湿度", "Min=0.0f, Max=100.0f",
                                             &climates[i].obj);
                climates[i].WindPower.init(5.0, "WindPower", "風力", "Min=0.0f, Max=100.0f",
                                           &climates[i].obj);
                climates[i].IgnitedLevel.init(0, "IgnitedLevel", "着火レベル", "Min=0, Max=3",
                                              &climates[i].obj);
                climates[i].FeatureColor.init({1, 1, 1, 1}, "FeatureColor", "", &climates[i].obj);
                climates[i].CalcRayleigh.init(1.0, "CalcRayleigh", "", "Min=-100.0f, Max=100.0f",
                                              &climates[i].obj);
                climates[i].CalcMieSymmetrical.init(1.0, "CalcMieSymmetrical", "",
                                                    "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].CalcMie.init(1.0, "CalcMie", "", "Min=-100.0f, Max=100.0f",
                                         &climates[i].obj);
                climates[i].CalcSfParamNear.init(0.0, "CalcSfParamNear", "",
                                                 "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].CalcSfParamAttenuation.init(
                    0.0, "CalcSfParamAttenuation", "", "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].CalcAmbientIntencity.init(1.0, "CalcAmbientIntencity", "",
                                                      "Min=-100.0f, Max=100.0f", &climates[i].obj);
                climates[i].CalcVolumeMaskIntencity.init(1.0, "CalcVolumeMaskIntencity", "",
                                                         "Min=-100.0f, Max=100.0f",
                                                         &climates[i].obj);
                climates[i].PaletteSetSelect.init(0, "PaletteSetSelect", "", "Min=0, Max=12",
                                                  &climates[i].obj);
                climates[i].FogType.init(0, "FogType", "", "Min=0, Max=1", &climates[i].obj);
                climates[i].ForbidComeback.init(false, "ForbidComeback", "", "Min=0, Max=1",
                                                &climates[i].obj);
                climates[i].BlueSkyRainPat.init(0, "BlueSkyRainPat", "", "Min=0, Max=3",
                                                &climates[i].obj);

                mWorldInfo.addObj(&climates[i].obj,
                                  sead::FormatFixedSafeString<128>("ClimateDefines_%d", i));
            }

            auto* env_mgr = getEnvMgr();

            for (int i = 0; i < EnvMgr::NumEnvAttributes; ++i) {
                mWorldInfo.addObj(&getEnvMgr()->mEnvAttributes[i].obj,
                                  sead::FormatFixedSafeString<128>("EnvAttribute_%d", i));
            }

            for (int i = 0; i < EnvMgr::NumWeatherInfluences; ++i) {
                mWorldInfo.addObj(&getEnvMgr()->mWeatherInfluences[i].obj,
                                  sead::FormatFixedSafeString<128>("WeatherInfluence_%d", i));
            }

            for (int i = 0; i < EnvMgr::NumRemains; ++i) {
                mWorldInfo.addObj(&getEnvMgr()->mRemains[i].obj,
                                  sead::FormatFixedSafeString<128>("Remains_%d", i));
            }

            auto& palettes = env_mgr->mEnvPalettes;
            for (int i = 0; i < EnvMgr::NumEnvPalettes; ++i) {
                mWorldInfo.addObj(&palettes(i).obj,
                                  sead::FormatFixedSafeString<128>("EnvPalette_%d", i));
            }

            mWorldInfo.addObj(&getEnvMgr()->mEnvPaletteStatic.obj,
                              sead::FormatFixedSafeString<128>("EnvPaletteStatic"));

            for (int i = 0; i < EnvMgr::NumCdanAddFog; ++i) {
                mWorldInfo.addObj(&getEnvMgr()->mCdanAddFog[i].obj,
                                  sead::FormatFixedSafeString<128>("EnvPalette_CdanAddFog%d", i));
            }

            mWorldInfo.addObj(&getEnvMgr()->mIndoorPalette.obj,
                              sead::FormatFixedSafeString<128>("IndoorPalette"));

            mWorldInfo.addObj(&getDofMgr()->mDofMgrParamObj,
                              sead::FormatFixedSafeString<128>("DofMgrParam"));

            auto& prc = getSkyMgr()->mPrCloud;
            auto& prcv = getSkyMgr()->mPrCloudV;
            auto& skypal0 = getSkyMgr()->mSkyPalette0;
            auto& skypal2 = getSkyMgr()->mSkyPalette2;
            auto& cloudpat0 = getSkyMgr()->mCloudPat0;
            auto& cloudpat2 = getSkyMgr()->mCloudPat2;
            auto& cloudspd = getSkyMgr()->mCloudSpd;

            for (int i = 0; i < SkyMgr::NumCloudPats; ++i) {
                mWorldInfo.addObj(&prc[i].mObj, sead::FormatFixedSafeString<128>("PrCloud_%d", i));
                mWorldInfo.addObj(&prcv[i][0].mObj,
                                  sead::FormatFixedSafeString<128>("PrCloudV0_%d", i));
                mWorldInfo.addObj(&prcv[i][1].mObj,
                                  sead::FormatFixedSafeString<128>("PrCloudV1_%d", i));
            }

            mWorldInfo.addObj(&Manager::instance()->getSkyMgr()->mSunParamObj,
                              sead::FormatFixedSafeString<128>("SunParam"));

            for (int i = 0; i < SkyMgr::NumSkyPalettes; ++i) {
                mWorldInfo.addObj(&skypal0[i].mObj,
                                  sead::FormatFixedSafeString<128>("SkyPalette0_%d", i));
                mWorldInfo.addObj(&skypal2[i].mObj,
                                  sead::FormatFixedSafeString<128>("SkyPalette2_%d", i));
            }

            for (int i = 0; i < SkyMgr::NumCloudPats; ++i) {
                mWorldInfo.addObj(&cloudpat0[i].mObj,
                                  sead::FormatFixedSafeString<128>("CloudPat0_%d", i));
                mWorldInfo.addObj(&cloudpat2[i].mObj,
                                  sead::FormatFixedSafeString<128>("CloudPat2_%d", i));
                mWorldInfo.addObj(&cloudspd[i].mObj,
                                  sead::FormatFixedSafeString<128>("CloudSpd_%d", i));
            }

            mDungeonEnv.mLightLongitude.init(135.0, "LightLongitude", "", "Min=-360.0f, Max=360.0f",
                                             &mDungeonEnv.mDungeonEnvObj);
            mDungeonEnv.mDungeonSize.init(sead::FormatFixedSafeString<128>("S"),
                                          sead::FormatFixedSafeString<128>("DungeonSize"), "",
                                          &mDungeonEnv.mDungeonEnvObj);
            mDungeonEnv.mDungeonType.init(sead::FormatFixedSafeString<128>("Gimmick"),
                                          sead::FormatFixedSafeString<128>("DungeonType"), "",
                                          &mDungeonEnv.mDungeonEnvObj);
            mDungeonEnv.addObj(&mDungeonEnv.mDungeonEnvObj,
                               sead::FormatFixedSafeString<128>("DungeonEnv"));
        }

        if (res)
            mWorldInfo.applyResParameterArchive(agl::utl::ResParameterArchive(res->getRawData()));
    }

    if (mStageType2 == StageType::Indoor) {
        sead::FixedSafeString<64> path;
        path.format("Map/DungeonData/CDungeon/%s", StageInfo::getCurrentMapName().cstr());
        path.appendWithFormat(".bdgnenv");
        auto* ksys_res =
            sead::DynamicCast<res::Resource>(mDungeonEnv.mResHandle.load(path.cstr(), &req));
        auto* res = sead::DynamicCast<sead::DirectResource>(ksys_res);
        if (res)
            mDungeonEnv.applyResParameterArchive(agl::utl::ResParameterArchive(res->getRawData()));
    }

    for (int i = 0; i < mWorldInfo.mClimates.size(); ++i) {
        mWorldInfo.mClimates[i].WindDirectionType = 0;
        mWorldInfo.mClimates[i].WindPowerMultiplier = 1.0f;
        mWindDirections[i] = 0.0f;
    }

    mWorldInfoLoadStatus = WorldInfoLoadStatus::Loaded;
    mManualWindSpeed = 5.0f;
    mEnableAutoWind = true;
    mWeatherType = WeatherType::Invalid;
    mTempDirectDayExtra = PlaceholderTemp;
#ifdef MATCHING_HACK_NX_CLANG
    auto s = mMgrs.size();
    // the optimiser can't do anything with this knowledge, but it forces s not to be optimized out
    __builtin_assume(s >= 0);
#endif
    mTempDirectNightExtra = PlaceholderTemp;
    mTempDirectDay = PlaceholderTemp;
    mTempDirectNight = PlaceholderTemp;
    mWindDir.x = 0;
    mWindDir.y = 0;
    mWindDir.z = -1;
    mWindDirectionType = 0;
    mManualWindTimer = 0;
    mWindChangeFinalTimer = 0;
    mWeatherTypeTimer = 0;
    _7d5 = false;
    mWeatherSetForDemo = false;
    mTempDirectTimer = 0;
    mTempDirectDayTimer = 0;
    mTempDirectNightTimer = 0;
    mDirectionalLightVecA = {0, 1, 0};
    mDirectionalLightVecB = {0, 1, 0};
    mDirectionalLightTimer = 0;
    _798 = -1;
    _79c = 0;

    getTimeMgr()->reset();
    getSkyMgr()->reset();
    getTempMgr()->reset();
    getWeatherMgr()->reset();
    getEnvMgr()->reset();
    getShootingStarMgr()->reset();
    getDofMgr()->reset();

    _7ac = 0;
    _770 = 0.0f;
    mIgnitedTimer = 0;
    mIgnitedLevel = 0;
    mIgnitedRadius = -1.0f;
    mIgnitedCenter = {0, 0, 0};
    updateRemainsType();
    updateGraphicsMap(mStageType);
    _720 = 0;
    _7b8 = 0;
    mFocusDist = 100.0f;
    updateFieldType();
    mMapEdgeWindDirectionType = 0;
    mMapEdgeWindSpeed = 1.0f;
    mMapEdgeWindEnabled = false;
}

void Manager::updateFieldType() {
    mScalingMode = ScalingMode::Enabled;

    if (StageInfo::getCurrentMapType().include("MainField")) {
        mFieldType = FieldType::MainField;
    } else if (StageInfo::getCurrentMapType().include("AocField")) {
        mFieldType = FieldType::AocField;
        mScalingMode = ScalingMode::Disabled;
    }
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
    return mWorldInfo.mClimates[int(climate)].WeatherBlueskyRate.ref();
}

int Manager::getWeatherCloudyRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].WeatherCloudyRate.ref();
}

int Manager::getWeatherRainRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].WeatherRainRate.ref();
}

int Manager::getWeatherHeavyRainRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].WeatherHeavyRainRate.ref();
}

int Manager::getWeatherStormRate(Climate climate) const {
    return mWorldInfo.mClimates[int(climate)].WeatherStormRate.ref();
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
