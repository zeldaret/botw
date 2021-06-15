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
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldDofMgr.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldShootingStarMgrEx.h"
#include "KingSystem/World/worldSkyMgr.h"
#include "KingSystem/World/worldTempMgr.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/World/worldWindMgr.h"

namespace sead {
class WorkerMgr;
}

namespace ksys::world {

struct ClimateInfo {
    static constexpr int NumClimateTemp = 11;

    agl::utl::Parameter<int> WeatherType;
    agl::utl::Parameter<int> WeatherBlueskyRate;
    agl::utl::Parameter<int> WeatherCloudyRate;
    agl::utl::Parameter<int> WeatherRainRate;
    agl::utl::Parameter<int> WeatherHeavyRainRate;
    agl::utl::Parameter<int> WeatherStormRate;
    agl::utl::Parameter<bool> DayLockBlueSky;
    agl::utl::Parameter<bool> NightLockBlueSky;
    sead::SafeArray<agl::utl::Parameter<float>, NumClimateTemp> ClimateTempDay;
    sead::SafeArray<agl::utl::Parameter<float>, NumClimateTemp> ClimateTempNight;
    agl::utl::Parameter<float> MoistureMax;
    agl::utl::Parameter<float> MoistureMin;
    agl::utl::Parameter<float> WindPower;
    agl::utl::ParameterObj obj;
    u32 WindDirectionType;
    float WindPowerMultiplier;
    agl::utl::Parameter<int> IgnitedLevel;
    agl::utl::Parameter<sead::Color4f> FeatureColor;
    agl::utl::Parameter<float> CalcRayleigh;
    agl::utl::Parameter<float> CalcMieSymmetrical;
    agl::utl::Parameter<float> CalcMie;
    agl::utl::Parameter<float> CalcSfParamNear;
    agl::utl::Parameter<float> CalcSfParamAttenuation;
    agl::utl::Parameter<float> CalcAmbientIntencity;
    agl::utl::Parameter<float> CalcVolumeMaskIntencity;
    agl::utl::Parameter<int> PaletteSetSelect;
    agl::utl::Parameter<int> FogType;
    agl::utl::Parameter<bool> ForbidComeback;
    agl::utl::Parameter<int> BlueSkyRainPat;
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
    agl::utl::Parameter<sead::FixedSafeString<32>> mDungeonType;
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
    void onStageInit(StageType stage_type, bool is_demo, bool is_main_field);
    void updateRemainsType();
    void updateGraphicsMap(StageType type);

    void initBeforeStageGen();
    void unload2();
    void clearArray();

    int getWeatherBlueskyRate(Climate climate) const;
    int getWeatherCloudyRate(Climate climate) const;
    int getWeatherRainRate(Climate climate) const;
    int getWeatherHeavyRainRate(Climate climate) const;
    int getWeatherStormRate(Climate climate) const;

    void calc1(sead::WorkerMgr* mgr);
    void calc2(sead::WorkerMgr* mgr);
    void calc3(sead::WorkerMgr* mgr);

    // TODO: more Chemical functions
    void updateChemicalFarObj();

    void calcEntryJob();

    void changeWind(int direction, bool enable_auto_wind, float speed);
    void setManualWind(bool enable_auto_wind, sead::Vector3f dir, float speed);
    void resetManualWind();

    void setDirectionalLight(float angle_x, float angle_y);
    void setDirectionalLightYang(float value);

    bool isGerudoDesertClimate() const;

    bool hasCameraOrPlayerMoved(float distance_threshold) const;

    int getDungeonSize() const;
    int getDungeonType() const;
    float getDungeonLightLongitude() const;

    void setCameraDistForRemainsElectric(sead::Vector3f pos);
    void setFocusDist(float dist);

    void rerollClimateWindPowers();
    void forceResetManualWind();
    void setTemperatureDay(float temp);
    void setTemperatureNight(float temp);
    void setIgnitedLevel(int level, float radius, sead::Vector3f center);

    void onEventFlowEnd();

    // TODO: more functions

    bool isMainField() const { return mIsMainField && mStageType == StageType::OpenWorld; }

    bool isAocField() const {
        return mStageType == StageType::OpenWorld && mFieldType == FieldType::AocField &&
               mScalingMode == ScalingMode::Disabled;
    }

    StageType getStageType() const { return mStageType; }
    FieldType getFieldType() const { return mFieldType; }
    ScalingMode getScalingMode() const { return mScalingMode; }
    CalcType getCalcType() const { return mCalcType; }

    TimeMgr* getTimeMgr() const { return static_cast<TimeMgr*>(mMgrs[0]); }
    SkyMgr* getSkyMgr() const { return static_cast<SkyMgr*>(mMgrs[1]); }
    ShootingStarMgr* getShootingStarMgr() const { return static_cast<ShootingStarMgr*>(mMgrs[2]); }
    WeatherMgr* getWeatherMgr() const { return static_cast<WeatherMgr*>(mMgrs[3]); }
    TempMgr* getTempMgr() const { return static_cast<TempMgr*>(mMgrs[4]); }
    WindMgr* getWindMgr() const { return static_cast<WindMgr*>(mMgrs[5]); }
    EnvMgr* getEnvMgr() const { return static_cast<EnvMgr*>(mMgrs[6]); }
    DofMgr* getDofMgr() const { return static_cast<DofMgr*>(mMgrs[7]); }
    ChemicalMgr* getChemicalMgr() const { return static_cast<ChemicalMgr*>(mMgrs[8]); }

    bool worldInfoLoaded() const { return mWorldInfoLoadStatus != WorldInfoLoadStatus::NotLoaded; }

private:
    enum class WorldInfoLoadStatus : u8 {
        NotLoaded,
        Loaded,
        Unloaded,
    };

    void overrideWindSpeed(float* wind_speed) const;

    void calcManagers(sead::WorkerMgr* worker_mgr);
    void updateOverrides();
    void updateTimers();
    void updateWindDirections();
    void updateFieldType();

    static constexpr float PlaceholderTemp = 99999.9;

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

    u32 mTicks = 0;
    int mTimer = 30;
    u32 _6c8 = 0;
    bool _6cc = false;
    bool mGameSceneInitialized = false;

    sead::SafeArray<float, NumClimates> mWindDirections;
    u32 _720 = 0;
    sead::Vector3f mWindDir{0, 0, -1};
    sead::Vector3f mDirectionalLightVecA{0, 1, 0};
    sead::Vector3f mDirectionalLightVecB{0, 1, 0};
    sead::Vector3f mIgnitedCenter{0, 0, 0};
    float mClimateTransitionProgress = 1.0;
    float mMapEdgeWindSpeed = 1.0;
    float mManualWindSpeed = 5.0;
    float mTempDirectDayExtra = PlaceholderTemp;
    float mTempDirectNightExtra = PlaceholderTemp;
    float mTempDirectDay = PlaceholderTemp;
    float mTempDirectNight = PlaceholderTemp;
    float _770 = 0.0;
    float mFocusDist = 100.0;
    float mIgnitedRadius = -1.0;
    u32 _77c = 9;
    Climate mCurrentClimate{};
    Climate mPrevClimate{};
    int mWindDirectionType = 0;
    int mManualWindTimer = 0;
    u32 mMapEdgeWindDirectionType = 0;
    int mWeatherTypeTimer = 0;
    int _798 = -1;
    int _79c = 0;
    int mTempDirectTimer = 0;
    int mTempDirectDayTimer = 0;
    int mTempDirectNightTimer = 0;
    u32 _7ac = 0;
    int mIgnitedTimer = 0;
    int mIgnitedLevel = 0;
    u32 _7b8 = 0;
    RemainsType mRemainsType{};
    FieldType mFieldType{};
    ScalingMode mScalingMode{};
    int mWindChangeFinalTimer = 0;
    float mWindSpeedAocField = 0.75;
    WorldInfoLoadStatus mWorldInfoLoadStatus = WorldInfoLoadStatus::NotLoaded;
    sead::SizedEnum<WeatherType, u8> mWeatherType = WeatherType::Invalid;
    u8 mDirectionalLightTimer = 0;
    bool mEnableAutoWind = true;
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
