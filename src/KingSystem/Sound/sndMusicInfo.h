#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
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
    virtual void init(sead::Heap* heap) {}

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
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterList mHeader;
    agl::utl::IParameterObj mData;

public:
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
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
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
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterList mData;

public:
    sead::Buffer<ParamPerType> mParamPerTypes;
};
KSYS_CHECK_SIZE_NX150(TemperatureBgmInfo, 0x238);

class SpotBgmInfo : public MusicInfo {
public:
    SpotBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
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
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
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
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
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
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
};
KSYS_CHECK_SIZE_NX150(BigMazeBgmInfo, 0x270);

class AnimalMasterBgmInfo : public MusicInfo {
public:
    AnimalMasterBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
};
KSYS_CHECK_SIZE_NX150(BigMazeBgmInfo, 0x270);

class FieldBattleBgmInfo : public MusicInfo {
public:
    FieldBattleBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
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
    void init(sead::Heap* heap) override;

protected:
    agl::utl::IParameterObj mData;

public:
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
};
KSYS_CHECK_SIZE_NX150(GolemBgmInfo, 0x2B0);

class GiantBgmInfo : public BossBgmInfo {
public:
    GiantBgmInfo();
};
KSYS_CHECK_SIZE_NX150(GiantBgmInfo, 0x2B0);

class SandwormBgmInfo : public BossBgmInfo {
public:
    SandwormBgmInfo();

private:
    agl::utl::Parameter<float> mAngryStartFadeSec;
    agl::utl::Parameter<float> mAngryEndFadeSec;
    agl::utl::Parameter<float> mChanceStartWaitSec;
};
KSYS_CHECK_SIZE_NX150(SandwormBgmInfo, 0x310);

class AssassinSeniorBgmInfo : public MusicInfo {
public:
    AssassinSeniorBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mToDemoFadeSec;
    agl::utl::Parameter<float> mToBattleFadeSec;
    agl::utl::Parameter<float> mFeelPlayingSec;
};
KSYS_CHECK_SIZE_NX150(AssassinSeniorBgmInfo, 0x290);

class GuardianBgmInfo : public MusicInfo {
public:
    GuardianBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeOutWaitSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mFeelPlayingSec;
    agl::utl::Parameter<int> mDamageThresholdHitReserve;
    agl::utl::Parameter<float> mCancelHitSec;
    agl::utl::Parameter<float> mIgnoreReserveCountDownSec;
    agl::utl::Parameter<unsigned int> mMarkerIdHitSectionB;
    agl::utl::Parameter<unsigned int> mMarkerIdHitSectionC;
    agl::utl::Parameter<unsigned int> mMarkerIdHitSectionA;
    agl::utl::Parameter<int> mMarkerCallbackOffsetSample;
};
KSYS_CHECK_SIZE_NX150(GuardianBgmInfo, 0x370);

class GuardianFixedBgmInfo : public MusicInfo {
public:
    GuardianFixedBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mFadeWaitSec;
    agl::utl::Parameter<float> mFeelPlayingSec;
};
KSYS_CHECK_SIZE_NX150(GuardianFixedBgmInfo, 0x290);

class DragonBgmInfo : public MusicInfo {
public:
    SEAD_ENUM(DragonEnum,DragonBgm,GrudgeDragonBgm)

    struct ParamPerType : public agl::utl::IParameterObj {
        agl::utl::Parameter<float> mDistanceThreshold;
        agl::utl::Parameter<float> mPlayWaitSec;
        agl::utl::Parameter<float> mFadeInSec;
        agl::utl::Parameter<float> mFadeWaitSec;
        agl::utl::Parameter<float> mFadeOutSec;

        ParamPerType();
    };

    DragonBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterList mData;

public:
    sead::Buffer<ParamPerType> mParamPerTypes;
};
KSYS_CHECK_SIZE_NX150(DragonBgmInfo, 0x238);

class GanonGrudgeBattleBgmInfo : public MusicInfo {
public:
    GanonGrudgeBattleBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mFadeInSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mFeelPlayingSec;
};
KSYS_CHECK_SIZE_NX150(GanonGrudgeBattleBgmInfo, 0x270);

class EventBgmRemainsElecBattleInfo : public MusicInfo {
public:
    EventBgmRemainsElecBattleInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mMinVolumeOutStorm;
    agl::utl::Parameter<float> mFadeInSecOutStorm;
    agl::utl::Parameter<float> mFadeOutSecOutStorm;
    agl::utl::Parameter<float> mMinVolumeWakeBoarding;
    agl::utl::Parameter<float> mFadeInSecWakeBoarding;
    agl::utl::Parameter<float> mFadeOutSecWakeBoarding;
};
KSYS_CHECK_SIZE_NX150(EventBgmRemainsElecBattleInfo, 0x2d0);

class EventBgmRemainsFireBattleInfo : public MusicInfo {
public:
    EventBgmRemainsFireBattleInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mFoundFadeOutSec;
    agl::utl::Parameter<float> mFoundWaitSec;
    agl::utl::Parameter<float> mFoundAgainWaitSec;
};
KSYS_CHECK_SIZE_NX150(EventBgmRemainsFireBattleInfo, 0x270);

class DungeonNormalBgmInfo : public MusicInfo {
public:
    struct PartChangeOdds : public agl::utl::IParameterObj {
        PartChangeOdds();
        agl::utl::Parameter<float> mOdds_1To1;
        agl::utl::Parameter<float> mOdds_2To1;
        agl::utl::Parameter<float> mOdds_2To2;
        agl::utl::Parameter<float> mOdds_3To2;
        agl::utl::Parameter<float> mOdds_3To3;
        agl::utl::Parameter<float> mOdds_4To3;
    };

    DungeonNormalBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterList mHeader;

public:
    sead::Buffer<PartChangeOdds> mPartChangeOdds;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<unsigned int> mLoopNumForOddsId2;
    agl::utl::Parameter<unsigned int> mLoopNumForOddsId3;
    agl::utl::Parameter<unsigned int> mMaxPartChainThreshold;
    agl::utl::Parameter<float> mOdds_FirstArp;
    agl::utl::Parameter<float> mTitleDelaySec;
};
KSYS_CHECK_SIZE_NX150(DungeonNormalBgmInfo, 0x308);

class DungeonRewardBgmInfo : public MusicInfo {
public:
    DungeonRewardBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mOddsPlayableString;
    agl::utl::Parameter<float> mTitleDelaySec;
};
KSYS_CHECK_SIZE_NX150(DungeonRewardBgmInfo, 0x250);

class DungeonBattleBgmInfo : public MusicInfo {
public:
    DungeonBattleBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mPlayWaitSec;
    agl::utl::Parameter<float> mFadeOutSec;
    agl::utl::Parameter<float> mVolumeNormal;
};
KSYS_CHECK_SIZE_NX150(DungeonBattleBgmInfo, 0x270);

class RemainsNormalBgmInfo : public MusicInfo {
public:
    RemainsNormalBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mFadeOutSecA;
    agl::utl::Parameter<float> mFadeOutSecB;
    agl::utl::Parameter<float> mFadeOutSecZ;
    agl::utl::Parameter<float> mCrossFadeSec;
};
KSYS_CHECK_SIZE_NX150(RemainsNormalBgmInfo, 0x290);

class TutorialDungeonBattleBgmInfo : public MusicInfo {
public:
    TutorialDungeonBattleBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mTransitionDelaySec;
    agl::utl::Parameter<float> mOutroDelaySec;
};
KSYS_CHECK_SIZE_NX150(TutorialDungeonBattleBgmInfo, 0x250);

class GanonBeastBgmInfo : public MusicInfo {
public:
    GanonBeastBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mStartDelaySec;
    agl::utl::Parameter<float> mRetryDelaySec;
    agl::utl::Parameter<float> m1To2TransitionDelaySec;
    agl::utl::Parameter<float> m2To3TransitionDelaySec;
    agl::utl::Parameter<float> mFadeOutSec;
};
KSYS_CHECK_SIZE_NX150(GanonBeastBgmInfo, 0x2b0);

class FinalTrialBossBattleBgmInfo : public MusicInfo {
public:
    FinalTrialBossBattleBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterObj mData;

public:
    agl::utl::Parameter<float> mTransformDemoWaitSec;
    agl::utl::Parameter<float> mFadeSecToTransformDemo;
    agl::utl::Parameter<unsigned int> mCurveTypeToTransformDemo;
    agl::utl::Parameter<float> mFadeSecFromTransformDemo;
    agl::utl::Parameter<unsigned int> mCurveTypeFromTransformDemo;
    agl::utl::Parameter<float> mFadeSeLevel3To4;
    agl::utl::Parameter<unsigned int> mCurveTypeLevel3To4;
    agl::utl::Parameter<float> mStopFadeSec;
};
KSYS_CHECK_SIZE_NX150(FinalTrialBossBattleBgmInfo, 0x310);

class EnvPaletteReactiveBgmInfo : public MusicInfo {
public:
    SEAD_ENUM(EnvPaletteReactiveBgmEnum,DLC2nd_OneHitKillTrial)

    struct ParamPerType : public agl::utl::IParameterObj {
        agl::utl::Parameter<float> mPlayWaitSec;
        agl::utl::Parameter<float> mFadeInSec;
        agl::utl::Parameter<float> mFadeOutSec;

        ParamPerType();
    };

    EnvPaletteReactiveBgmInfo();
    void init(sead::Heap* heap) override;

private:
    agl::utl::IParameterList mData;

public:
    sead::Buffer<ParamPerType> mParamPerTypes;
};
KSYS_CHECK_SIZE_NX150(EnvPaletteReactiveBgmInfo, 0x238);

}  // namespace ksys::snd
