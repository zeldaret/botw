#pragma once

#include <container/seadPtrArray.h>
#include <mc/seadJobQueue.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/ParamIO.h"
#include "agl/Utils/aglAtomicPtrArray.h"
#include "agl/Utils/aglParameter.h"
#include "agl/Utils/aglParameterObj.h"

namespace ksys::world {

class Climate {};

class WorldInfo : public ParamIO {
public:
    WorldInfo() : ParamIO("winfo", 0) {}
    ~WorldInfo();

    bool ParamIO_m0() override { return true; }

    res::Handle mResHandle;
    u32 mNumClimates = 0;
    Climate* mClimates = nullptr;
};

class DungeonEnv : public ParamIO {
public:
    DungeonEnv() : ParamIO("dgenv", 0) {}
    ~DungeonEnv();

    bool ParamIO_m0() override { return true; }

    res::Handle mResHandle;

    agl::utl::Parameter<f32> mLightLongitude;
    agl::utl::Parameter<sead::FixedSafeString<32>> mDungeonSize;
    agl::utl::Parameter<sead::FixedSafeString<32>> mString538;
    agl::utl::ParameterObj mDungeonEnvObj;
    sead::PtrArray<void*> mgrs{};
    sead::DirectResource* mInfoRes = nullptr;
};

// FIXME: incomplete
class Manager : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    bool isRaining(const sead::Vector3f& pos) const;

    WorldInfo mWorldInfo;
    DungeonEnv mDungeonEnv;

    agl::utl::AtomicPtrArray<void*> mAtomicPtrArray{0, 0};
    u32 _5e0 = 1;
    u32 mCalcType = 3;
    sead::FixedSizeJQ mJobQueue;
    f32 mWindPowerIf78C = 5.0;
    f32 mTempDirectDayExtra = 100000.0;
    f32 mTempDirectNightExtra = 100000.0;
    f32 mTempDirectDay = 100000.0;
    f32 mTempDirectNight = 100000.0;
    s32 _794;
    s32 mStageType = 0;
    s32 mStageType2 = 0;
    u8 mGameSceneInitialised = 0;
    sead::Vector3f mPrevPlayerPos{};
    sead::Vector3f mPlayerPos{};
    sead::Vector3f mPrevCameraPos{};
    sead::Vector3f mCameraPos{};
    f32 _770 = 0.0;
    s32 _778 = 0;
    s32 _78c = 0;
    s32 _7ac = 0;
    void* _7a4 = nullptr;
    void* _79c = nullptr;
    f32 mWindPowerAocField = 0.75;
    u8 mWorldInfoLoaded = 0;
    u8 mWeatherType = 0xFF;
    u8 _7d2 = 0;
    u8 _7d3 = 1;
    u8 _7d4 = 0;
    u8 mInFinalTrialBossBattleArea = 0;
};

}  // namespace ksys::world
