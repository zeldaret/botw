#pragma once

#include <agl/Utils/aglAtomicPtrArray.h>
#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <mc/seadJobQueue.h>
#include <prim/seadSizedEnum.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldCloudMgr.h"
#include "KingSystem/World/worldDofMgr.h"
#include "KingSystem/World/worldShootingStarMgrEx.h"
#include "KingSystem/World/worldSkyMgr.h"
#include "KingSystem/World/worldTempMgr.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/World/worldWindMgr.h"

namespace ksys::world {

enum class CalcType {
    _0 = 0,
    _1 = 1,
    _2 = 2,
    Invalid = 3,
};

enum class StageType {
    Invalid = 0,
    OpenWorld = 1,
    Indoor = 2,
    OpenWorldTest = 3,
    MainFieldDungeon = 4,
    Viewer = 5,
};

enum class RemainsType {

};

enum class FieldType {
    MainField = 0,
    AocField = 1,
};

enum class ScalingMode {
    Enabled = 0,
    Disabled = 1,
};

enum class WeatherType {
    Bluesky,
    Cloudy,
    Rain,
    HeavyRain,
    Snow,
    HeavySnow,
    ThunderStorm,
    ThunderRain,
    BlueskyRain,
    Invalid = 0xff,
};
constexpr u32 NumWeatherTypes = 9;

enum class Climate {
    HyrulePlainClimate,
    NorthHyrulePlainClimate,
    HebraFrostClimate,
    TabantaAridClimate,
    FrostClimate,
    GerudoDesertClimate,
    GerudoPlateauClimate,
    EldinClimateLv0,
    TamourPlainClimate,
    ZoraTemperateClimate,
    HateruPlainClimate,
    FiloneSubtropicalClimate,
    SouthHateruHumidTemperateClimate,
    EldinClimateLv1,
    EldinClimateLv2,
    // sic
    DarkWoodsClimat,
    LostWoodClimate,
    GerudoFrostClimate,
    KorogForest,
    GerudoDesertClimateLv2,
};
constexpr u32 NumClimates = 20;

struct ClimateInfo {
    static constexpr int NumClimateTemp = 11;

    agl::utl::Parameter<int> weatherType;
    agl::utl::Parameter<int> weatherBlueskyRate;
    agl::utl::Parameter<int> weatherCloudyRate;
    agl::utl::Parameter<int> weatherRainRate;
    agl::utl::Parameter<int> weatherHeavyRainRate;
    agl::utl::Parameter<int> weatherStormRate;
    agl::utl::Parameter<bool> dayLockBlueSky;
    agl::utl::Parameter<bool> nightLockBlueSky;
    sead::SafeArray<agl::utl::Parameter<float>, NumClimateTemp> climateTempDay;
    sead::SafeArray<agl::utl::Parameter<float>, NumClimateTemp> climateTempNight;
    agl::utl::Parameter<float> moistureMax;
    agl::utl::Parameter<float> moistureMin;
    agl::utl::Parameter<float> windPower;
    agl::utl::ParameterObj obj;
    u32 windDirectionType;
    float windPowerMultiplier;
    agl::utl::Parameter<int> ignitedLevel;
    agl::utl::Parameter<sead::Color4f> featureColor;
    agl::utl::Parameter<float> _4a0;
    agl::utl::Parameter<float> _4c0;
    agl::utl::Parameter<float> _4e0;
    agl::utl::Parameter<float> _500;
    agl::utl::Parameter<float> _520;
    agl::utl::Parameter<float> _540;
    agl::utl::Parameter<float> _560;
    agl::utl::Parameter<int> paletteSetSelect;
    agl::utl::Parameter<int> fogType;
    agl::utl::Parameter<bool> forbidComeback;
    agl::utl::Parameter<int> _5e0;
};
KSYS_CHECK_SIZE_NX150(ClimateInfo, 0x600);

class WorldInfo : public agl::utl::IParameterIO, public sead::hostio::Node {
public:
    WorldInfo() : agl::utl::IParameterIO("winfo", 0) {}

    u8 _1d8[0x20];
    res::Handle mResHandle;
    sead::Buffer<ClimateInfo> mClimates;
};
KSYS_CHECK_SIZE_NX150(WorldInfo, 0x258);

class DungeonEnv : public agl::utl::IParameterIO, public sead::hostio::Node {
public:
    DungeonEnv() : agl::utl::IParameterIO("dgnenv", 0) {}

    u8 _1d8[0x20];
    res::Handle mResHandle;
    agl::utl::Parameter<float> mLightLongitude;
    agl::utl::Parameter<sead::FixedSafeString<32>> mDungeonSize;
    agl::utl::Parameter<sead::FixedSafeString<32>> mString538;
    agl::utl::ParameterObj mDungeonEnvObj;
};
KSYS_CHECK_SIZE_NX150(DungeonEnv, 0x338);

// FIXME: incomplete
class Manager : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    WeatherType getWeatherType() const;
    void setWeatherType(WeatherType weather_type, bool x, bool y, bool for_demo);
    void setWeatherType(const sead::SafeString& weather_type, bool x, bool y, bool for_demo);
    static const char* getWeatherTypeString(WeatherType type);

    Climate getClimate(const sead::Vector3f& pos) const;
    Climate getCurrentClimate() const;
    Climate getPrevClimate() const;
    float getClimateTransitionProgress() const;

    bool isDayLockBlueSky(Climate climate) const;
    bool isNightLockBlueSky(Climate climate) const;

    bool isRaining(const sead::Vector3f& pos) const;

    float calcTempDay(float height) const;
    float calcTempNight(float height) const;

    float getMoistureMax() const;
    float getMoistureMin() const;

    sead::Vector3f getWindDirection() const;
    float getWindSpeed() const;
    float getWindSpeed(const sead::Vector3f& pos) const;
    sead::Vector3f getWindDirection(const sead::Vector3f& pos) const;

    int getIgnitedLevel(const sead::Vector3f& pos) const;

    int getPaletteSetSelect() const;
    int getFogType() const;
    bool isForbidComeback() const;
    bool isForbidComeback(Climate climate) const;

    void unload();
    void init(sead::Heap* heap);
    void resetForStageUnload();
    void loadWorldInfoRes();
    void loadWorldInfo();
    void updateRemainsType();
    void updateGraphicsMap(StageType type);

    bool isMainField() const { return mIsMainField && mStageType == StageType::OpenWorld; }

    bool isAocField() const {
        return mStageType == StageType::OpenWorld && mFieldType == FieldType::AocField &&
               mScalingMode == ScalingMode::Disabled;
    }

    CalcType getCalcType() const { return mCalcType; }

    TimeMgr* getTimeMgr() const { return static_cast<TimeMgr*>(mMgrs[0]); }
    CloudMgr* getCloudMgr() const { return static_cast<CloudMgr*>(mMgrs[1]); }
    ShootingStarMgr* getShootingStarMgr() const { return static_cast<ShootingStarMgr*>(mMgrs[2]); }
    WeatherMgr* getWeatherMgr() const { return static_cast<WeatherMgr*>(mMgrs[3]); }
    TempMgr* getTempMgr() const { return static_cast<TempMgr*>(mMgrs[4]); }
    WindMgr* getWindMgr() const { return static_cast<WindMgr*>(mMgrs[5]); }
    SkyMgr* getSkyMgr() const { return static_cast<SkyMgr*>(mMgrs[6]); }
    DofMgr* getDofMgr() const { return static_cast<DofMgr*>(mMgrs[7]); }
    ChemicalMgr* getChemicalMgr() const { return static_cast<ChemicalMgr*>(mMgrs[8]); }

private:
    enum class WorldInfoLoadStatus : u8 {
        NotLoaded,
        Loaded,
        Unloaded,
    };

    bool worldInfoLoaded() const { return mWorldInfoLoadStatus != WorldInfoLoadStatus::NotLoaded; }

    void overrideWindSpeed(float* wind_speed) const;

    WorldInfo mWorldInfo;
    DungeonEnv mDungeonEnv;
    sead::DirectResource* mInfoRes{};

    sead::PtrArray<Job> mMgrs;
    agl::utl::AtomicPtrArray<void*> mAtomicPtrArray;
    sead::BitFlag32 _5e0 = 1;
    CalcType mCalcType = CalcType::Invalid;
    sead::FixedSizeJQ mJobQueue;

    sead::Vector3f mCameraPos{0, 0, 0};
    sead::Vector3f mPrevCameraPos{0, 0, 0};
    sead::Vector3f mPlayerPos{0, 0, 0};
    sead::Vector3f mPrevPlayerPos{0, 0, 0};

    StageType mStageType{};
    StageType mStageType2{};

    u32 _6c0 = 0;
    u32 _6c4 = 30;
    u32 _6c8 = 0;
    bool _6cc = false;
    bool mGameSceneInitialized = false;

    sead::SafeArray<float, NumClimates> mWindDirections;
    u32 _720 = 0;
    sead::Vector3f mWindDir{0, 0, -1};
    sead::Vector3f mDirectionalLightVecA{0, 1, 0};
    sead::Vector3f mDirectionalLightVecB{0, 1, 0};
    sead::Vector3f _748{0, 0, 0};
    float mClimateTransitionProgress = 1.0;
    float mMapEdgeWindSpeed = 1.0;
    float mManualWindSpeed = 5.0;
    float mTempDirectDayExtra = 99999.9;
    float mTempDirectNightExtra = 99999.9;
    float mTempDirectDay = 99999.9;
    float mTempDirectNight = 99999.9;
    float _770 = 0.0;
    float mFocusDist = 100.0;
    float _778 = -1.0;
    u32 _77c = 9;
    Climate mCurrentClimate{};
    Climate mPrevClimate{};
    u32 mWindDirectionType = 0;
    u32 mManualWindTimer = 0;
    u32 mMapEdgeWindDirectionType = 0;
    u32 _794 = 0;
    int _798 = -1;
    u32 _79c = 0;
    u32 _7a0 = 0;
    u32 _7a4 = 0;
    u32 _7a8 = 0;
    u32 _7ac = 0;
    u32 _7b0 = 0;
    u32 mIgnitedLevel = 0;
    u32 _7b8 = 0;
    RemainsType mRemainsType{};
    FieldType mFieldType{};
    ScalingMode mScalingMode{};
    u32 mWindChangeFinalTimer = 0;
    float mWindSpeedAocField = 0.75;
    WorldInfoLoadStatus mWorldInfoLoadStatus = WorldInfoLoadStatus::NotLoaded;
    sead::SizedEnum<WeatherType, u8> mWeatherType = WeatherType::Invalid;
    u8 mDirectionalLightTimer = 0;
    bool mWindChangesEnabled = true;
    bool mMapEdgeWindEnabled = false;
    bool _7d5 = false;
    bool mWeatherSetForDemo = false;
    u8 _7d7 = 0;
    bool mIsDemo = false;
    bool mIsMainField = false;
    bool mIsBattleCurseR = false;
    bool mInFinalTrialBossBattleArea = false;
};
KSYS_CHECK_SIZE_NX150(Manager, 0x7e0);

}  // namespace ksys::world
