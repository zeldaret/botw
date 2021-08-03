#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

class MusicInfo : public agl::utl::IParameterIO {
public:
    template <typename T>
    struct MinMax : public agl::utl::IParameterObj {
        MinMax(T min, T max, const sead::SafeString& name, const sead::SafeString& label,
               const sead::SafeString& meta, agl::utl::IParameterList* parent)
            : mLabel(label), mMeta(meta), mMin(min, "Min", "最小", mMeta, this),
              mMax(max, "Max", "最大", mMeta, this) {
            parent->addObj(this, name);
        }

        sead::FixedSafeString<64> mLabel;
        sead::FixedSafeString<32> mMeta;
        agl::utl::Parameter<T> mMin;
        agl::utl::Parameter<T> mMax;
    };

    MusicInfo() : IParameterIO("mscinfo", 0) {}

protected:
    void applySoundResource();

private:
    // TODO: 0x7101015628, requires `Sound` and `snd::ResourceMgr`
    sead::DirectResource* loadMusic();

protected:
    sead::SafeString mBgmTypeName;
};

class EnvBgmInfo : public MusicInfo {
public:
    SEAD_ENUM(EnvTimeEnum,EnvDayBgm,EnvNightBgm)

    struct ParamPerType : public agl::utl::IParameterObj {
        ParamPerType();

        agl::utl::Parameter<unsigned int> mBpm;
        agl::utl::Parameter<unsigned int> mPart0FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart1FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart2FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart3FirstWaitCount;
    };
    KSYS_CHECK_SIZE_NX150(ParamPerType, 0xD0);

    EnvBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterList mHeader;
    agl::utl::IParameterObj mData;
    sead::Buffer<EnvBgmInfo::ParamPerType> mParamPerTypes;
    agl::utl::Parameter<float> mEnableWaitSec;
    agl::utl::Parameter<int> mDistanceOfCheckingActiveEnemy;
    agl::utl::Parameter<float> mTimeDay;
    agl::utl::Parameter<float> mTimeNight;
    MinMax<float> mConstVolume;
    MinMax<float> mConstPan;
    agl::utl::Parameter<unsigned int> mMasterBeatBase;
    MinMax<int> mMasterBeatRate;
    MinMax<float> mPart0Volume;
    MinMax<float> mPart0Pan;
    agl::utl::Parameter<unsigned int> mPart1SegmentAWaitCountBase;
    MinMax<unsigned int> mPart1SegmentAWaitCountRate;
    agl::utl::Parameter<unsigned int> mPart1SegmentBWaitCountBase;
    MinMax<unsigned int> mPart1SegmentBWaitCountRate;
    agl::utl::Parameter<unsigned int> mPart1SegmentCWaitCountBase;
    MinMax<unsigned int> mPart1SegmentCWaitCountRate;
    MinMax<float> mPart1Volume;
    MinMax<float> mPart1Pan;
    agl::utl::Parameter<unsigned int> mPart2WaitCountBase;
    MinMax<unsigned int> mPart2WaitCountRate;
    MinMax<float> mPart2Volume;
    agl::utl::Parameter<unsigned int> mPart3WaitCountBase;
    MinMax<unsigned int> mPart3WaitCountRate;
    MinMax<float> mPart3Volume;
    MinMax<float> mPart3Pan;
};
KSYS_CHECK_SIZE_NX150(EnvBgmInfo, 0x12A8);

class HorseBgmInfo : public MusicInfo {
public:
    HorseBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mTimeDay;
    agl::utl::Parameter<float> mTimeNight;
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mMinVolume;
    agl::utl::Parameter<float> mFadeOutWaitSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mPlayingSecUseOutro;
    agl::utl::Parameter<float> mIgnoreRequestSec;
};
KSYS_CHECK_SIZE_NX150(HorseBgmInfo, 0x330);

class TemperatureBgmInfo : public MusicInfo {
public:
    SEAD_ENUM(TemperatureEnum,ColdBgm,HotBgm,BurnBgm)

    struct ParamPerType : public agl::utl::IParameterObj {
        ParamPerType();

        agl::utl::Parameter<float> mTemperatureThreshold;
        agl::utl::Parameter<float> mFadeOutSec;
        agl::utl::Parameter<float> mCancelFadeSec;
    };
    KSYS_CHECK_SIZE_NX150(ParamPerType, 0x90);

    TemperatureBgmInfo() = default;
    ~TemperatureBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterList mData;
    sead::Buffer<ParamPerType> mParamPerTypes;
};
KSYS_CHECK_SIZE_NX150(TemperatureBgmInfo, 0x238);

class SpotBgmInfo : public MusicInfo {
public:
    SpotBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mTimeDay;
    agl::utl::Parameter<float> mTimeNight;
    agl::utl::Parameter<float> mFilterOnFadeSec;
    agl::utl::Parameter<float> mFilterOffFadeSec;
    agl::utl::Parameter<float> mFilterValueLo;
    agl::utl::Parameter<float> mFilterValueHi;
    agl::utl::Parameter<float> mSubTrackNearDistance;
    agl::utl::Parameter<float> mSubTrackFarDistance;
    agl::utl::Parameter<float> mSubTrackVolumeMaxDelta;
    agl::utl::Parameter<float> mAllowFadeInSec;
    agl::utl::Parameter<float> mAllowFadeOutSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mCullingYFadeOutSec;
    agl::utl::Parameter<float> mCullingYFadeInSec;
};
KSYS_CHECK_SIZE_NX150(SpotBgmInfo, 0x3D0);

class MazeForestBgmInfo : public MusicInfo {
public:
    MazeForestBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mVolumeNormal;
    agl::utl::Parameter<float> mLostBoostSec;
    agl::utl::Parameter<float> mLostBoostCancelSec;
};
KSYS_CHECK_SIZE_NX150(MazeForestBgmInfo, 0x2D0);

class CastleBgmInfo : public MusicInfo {
public:
    CastleBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mFadeOutWaitSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mToIndoorWaitSec;
    agl::utl::Parameter<float> mToIndoorFadeSec;
    agl::utl::Parameter<float> mToOutdoorFadeSec;
    agl::utl::Parameter<float> mBattleWaitSec;
    agl::utl::Parameter<float> mBattleFadeInSec;
    agl::utl::Parameter<float> mBattleFadeOutSec;
};
KSYS_CHECK_SIZE_NX150(CastleBgmInfo, 0x310);

class BigMazeBgmInfo : public MusicInfo {
public:
    BigMazeBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
};
KSYS_CHECK_SIZE_NX150(BigMazeBgmInfo, 0x270);

class AnimalMasterBgmInfo : public MusicInfo {
public:
    AnimalMasterBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
};
KSYS_CHECK_SIZE_NX150(BigMazeBgmInfo, 0x270);

class FieldBattleBgmInfo : public MusicInfo {
public:
    FieldBattleBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<unsigned int> mBpm;
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mFeelPlayingSec;
    agl::utl::Parameter<float> mEasy1_OddsByKey0;
    agl::utl::Parameter<float> mEasy1_OddsByKey1;
    agl::utl::Parameter<float> mEasy1R_OddsBySameKey;
    agl::utl::Parameter<float> mEasy5_OddsBySameKey;
    agl::utl::Parameter<float> mMiddle0_OddsBySameKey;
    agl::utl::Parameter<float> mHard0_OddsBySameKey;
    agl::utl::Parameter<float> mHard1_OddsBySameKey;
    agl::utl::Parameter<float> mHard1F_OddsBySameKey;
    agl::utl::Parameter<float> mOddsByKeySubId0;
    agl::utl::Parameter<int> mTension_SkipEasy2;
    agl::utl::Parameter<int> mTension_SkipEasy5;
    agl::utl::Parameter<int> mTension_SkipMiddle1;
    agl::utl::Parameter<int> mTension_SkipHard;
    agl::utl::Parameter<unsigned int> mReserveHitWaitBeat;
    agl::utl::Parameter<unsigned int> mHitChainGridThreshold;
    agl::utl::Parameter<unsigned int> mIgnoreReserveHitGrid_Chain0;
    agl::utl::Parameter<unsigned int> mIgnoreReserveHitGrid_Chain1;
    agl::utl::Parameter<unsigned int> mIgnoreReserveHitGrid_Chain2;
    agl::utl::Parameter<int> mStopMainBgmWaitBeat;
    agl::utl::Parameter<unsigned int> mReserveOutroWaitBeat;
};
KSYS_CHECK_SIZE_NX150(FieldBattleBgmInfo, 0x530);

class BossBgmInfo : public MusicInfo {
public:
    BossBgmInfo();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterObj mData;
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mOutroWaitSec;
    agl::utl::Parameter<float> mChangeTypeFadeOutSec;
    agl::utl::Parameter<float> mFeelPlayingSec;
};
KSYS_CHECK_SIZE_NX150(BossBgmInfo, 0x2B0);

class GolemBgmInfo : public BossBgmInfo {
public:
    GolemBgmInfo();
    void init(sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(GolemBgmInfo, 0x2B0);

class GiantBgmInfo : public BossBgmInfo {
public:
    GiantBgmInfo();
    void init(sead::Heap* heap);
};
KSYS_CHECK_SIZE_NX150(GiantBgmInfo, 0x2B0);

}  // namespace ksys::snd
