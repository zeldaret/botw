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
        inline MinMax(T min, T max, const sead::SafeString& name, const sead::SafeString& label,
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
    // TODO: 0x7101015628, requires `Sound` and `snd::ResourceMgr`
    sead::DirectResource* loadMusic();

protected:
    sead::SafeString mBgmTypeName;
};

// TODO rename this to EnvBgm
class MusicParam : public MusicInfo {
public:
    SEAD_ENUM(EnvTimeEnum,EnvDayBgm,EnvNightBgm)

    struct ParamPerType : public agl::utl::IParameterObj {
        ParamPerType();

        agl::utl::Parameter<unsigned int> mBPM;
        agl::utl::Parameter<unsigned int> mPart0FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart1FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart2FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart3FirstWaitCount;
    };
    KSYS_CHECK_SIZE_NX150(ParamPerType, 0xD0);

    MusicParam();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterList mHeader;
    agl::utl::IParameterObj mData;
    sead::Buffer<MusicParam::ParamPerType> mParamPerTypes;
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
KSYS_CHECK_SIZE_NX150(MusicParam, 0x12A8);

class HorseBgm : public MusicInfo {
public:
    HorseBgm();
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
KSYS_CHECK_SIZE_NX150(HorseBgm, 0x330);

class TemperatureBgm : public MusicInfo {
public:
    SEAD_ENUM(TemperatureEnum,ColdBgm,HotBgm,BurnBgm)

    struct ParamPerType : public agl::utl::IParameterObj {
        ParamPerType();

        agl::utl::Parameter<float> mTemperatureThreshold;
        agl::utl::Parameter<float> mFadeOutSec;
        agl::utl::Parameter<float> mCancelFadeSec;
    };
    KSYS_CHECK_SIZE_NX150(ParamPerType, 0x90);

    TemperatureBgm();
    void init(sead::Heap* heap);

private:
    agl::utl::IParameterList mData;
    sead::Buffer<ParamPerType> mParamPerTypes;
};
KSYS_CHECK_SIZE_NX150(TemperatureBgm, 0x238);

}  // namespace ksys::snd
