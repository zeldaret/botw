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

    MusicInfo();

protected:
    sead::SafeString field_1D0;
    agl::utl::ParameterList mHeader;
};

class MusicParam : public MusicInfo {
public:
    struct OtherSub : public agl::utl::IParameterObj {
        OtherSub();

        agl::utl::Parameter<unsigned int> mBPM;
        agl::utl::Parameter<unsigned int> mPart0FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart1FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart2FirstWaitCount;
        agl::utl::Parameter<unsigned int> mPart3FirstWaitCount;
    };

    MusicParam();

private:
    agl::utl::ParameterObj mData;
    sead::Buffer<MusicParam::OtherSub> field_258;
    agl::utl::Parameter<float> mEnableWaitSec;
    agl::utl::Parameter<int> mDistanceOfCheckingActiveEnemy;
    agl::utl::Parameter<float> mTimeDay;
    agl::utl::Parameter<float> mTimeNight;
    ksys::snd::MusicInfo::MinMax<float> mConstVolume;
    ksys::snd::MusicInfo::MinMax<float> mConstPan;
    agl::utl::Parameter<unsigned int> mMasterBeatBase;
    ksys::snd::MusicInfo::MinMax<int> mMasterBeatRate;
    ksys::snd::MusicInfo::MinMax<float> mPart0Volume;
    ksys::snd::MusicInfo::MinMax<float> mPart0Pan;
    agl::utl::Parameter<unsigned int> mPart1SegmentAWaitCountBase;
    ksys::snd::MusicInfo::MinMax<unsigned int> mPart1SegmentAWaitCountRate;
    agl::utl::Parameter<unsigned int> mPart1SegmentBWaitCountBase;
    ksys::snd::MusicInfo::MinMax<unsigned int> mPart1SegmentBWaitCountRate;
    agl::utl::Parameter<unsigned int> mPart1SegmentCWaitCountBase;
    ksys::snd::MusicInfo::MinMax<unsigned int> mPart1SegmentCWaitCountRate;
    ksys::snd::MusicInfo::MinMax<float> mPart1Volume;
    ksys::snd::MusicInfo::MinMax<float> mPart1Pan;
    agl::utl::Parameter<unsigned int> mPart2WaitCountBase;
    ksys::snd::MusicInfo::MinMax<unsigned int> mPart2WaitCountRate;
    ksys::snd::MusicInfo::MinMax<float> mPart2Volume;
    agl::utl::Parameter<unsigned int> mPart3WaitCountBase;
    ksys::snd::MusicInfo::MinMax<unsigned int> mPart3WaitCountRate;
    ksys::snd::MusicInfo::MinMax<float> mPart3Volume;
    ksys::snd::MusicInfo::MinMax<float> mPart3Pan;
};
KSYS_CHECK_SIZE_NX150(MusicParam, 0x12A8);

}  // namespace ksys::snd
