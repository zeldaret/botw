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

protected:
    sead::SafeString mBgmTypeName;
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
    agl::utl::ParameterList mHeader;
    agl::utl::ParameterObj mData;
    sead::Buffer<MusicParam::OtherSub> field_258;
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

}  // namespace ksys::snd
