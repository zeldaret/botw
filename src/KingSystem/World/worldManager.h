#pragma once

#include <agl/Utils/aglAtomicPtrArray.h>
#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <mc/seadJobQueue.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::world {

// FIXME
class Climate {};

class WorldInfo : public agl::utl::IParameterIO, public sead::hostio::Node {
public:
    WorldInfo() : agl::utl::IParameterIO("winfo", 0) {}

    u8 _1d8[0x20];
    res::Handle mResHandle;
    sead::Buffer<Climate> mClimates;
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
    enum class CalcType {
        _3 = 3,
    };

    enum class StageType {

    };

    enum class RemainsType {

    };

    enum class FieldType {

    };

    enum class ScalingMode {

    };

    bool isRaining(const sead::Vector3f& pos) const;

    WorldInfo mWorldInfo;
    DungeonEnv mDungeonEnv;
    sead::DirectResource* mInfoRes{};

    sead::PtrArray<void*> mMgrs;
    agl::utl::AtomicPtrArray<void*> mAtomicPtrArray;
    sead::BitFlag32 _5e0 = 1;
    CalcType mCalcType = CalcType::_3;
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

    float mFloatsPerClimate[20];
    u32 _720 = 0;
    sead::Vector3f mWindDir{0, 0, -1};
    sead::Vector3f mDirectionalLightVecA{0, 1, 0};
    sead::Vector3f mDirectionalLightVecB{0, 1, 0};
    sead::Vector3f _748{0, 0, 0};
    float _754 = 1.0;
    float mWindPowerIf7D4 = 1.0;
    float mWindPowerIf78C = 5.0;
    float mTempDirectDayExtra = 99999.9;
    float mTempDirectNightExtra = 99999.9;
    float mTempDirectDay = 99999.9;
    float mTempDirectNight = 99999.9;
    float _770 = 0.0;
    float mFocusDist = 100.0;
    float _778 = -1.0;
    u32 _77c = 9;
    u32 mCurrentArea = 0;
    u32 mPrevArea = 0;
    u32 _788 = 0;
    u32 _78c = 0;
    u32 _790 = 0;
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
    u32 _7c8 = 0;
    float mWindPowerAocField = 0.75;
    bool mWorldInfoLoaded = false;
    u8 mWeatherType = 0xFF;
    u8 _7d2 = 0;
    u8 _7d3 = 1;
    u8 _7d4 = 0;
    u8 _7d5 = 0;
    u8 _7d6 = 0;
    u8 _7d7 = 0;
    bool mIsDemo = false;
    bool mIsMainField = false;
    bool mIsBattleCurseR = false;
    bool mInFinalTrialBossBattleArea = false;
};
KSYS_CHECK_SIZE_NX150(Manager, 0x7e0);

}  // namespace ksys::world
