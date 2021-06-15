#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class Demo : public sead::DirectResource, public agl::utl::IParameterIO {
public:
    Demo();

    static void registerFactory(sead::Heap* heap);

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

    agl::utl::ParameterObj mDemoSettingObj;
    agl::utl::ParameterObj mProgressObj;

    agl::utl::Parameter<sead::Vector3f> mLocation;
    agl::utl::Parameter<sead::FixedSafeString<32>> mWeather;
    agl::utl::Parameter<f32> mTime;
    agl::utl::Parameter<sead::FixedSafeString<32>> mStartType;
    agl::utl::Parameter<sead::FixedSafeString<32>> mNoEntryActors;
    agl::utl::Parameter<sead::FixedSafeString<32>> mSaveType;
    agl::utl::Parameter<sead::FixedSafeString<32>> mExtension;
    agl::utl::Parameter<bool> mIsFlashbackDemo;
    agl::utl::Parameter<sead::Vector3f> mOverwritePlayerPos;
    agl::utl::Parameter<bool> mIsOverwritePlayerPos;
    agl::utl::Parameter<sead::SafeString> mMapProjectName;
    agl::utl::Parameter<sead::SafeString> mMapResourceName;
    agl::utl::Parameter<bool> mIsStartupDemo;
    agl::utl::Parameter<sead::SafeString> mProgress;
    agl::utl::Parameter<sead::SafeString> mProductFormat;
    agl::utl::Parameter<sead::SafeString> mNextDemo;
    agl::utl::Parameter<bool> mIsStopChemical;

    agl::utl::Parameter<bool> mIsMovePlayerEndPos;
    agl::utl::Parameter<sead::Vector3f> mPlayerEndPos;

    agl::utl::Parameter<sead::FixedSafeString<32>> mStartLocationType;
    agl::utl::Parameter<sead::FixedSafeString<32>> mEventMode;
    agl::utl::Parameter<bool> mWithTransAnimation;

    agl::utl::Parameter<f32> mOverwritePlayerRotY;
    agl::utl::Parameter<f32> mPlayerEndRotY;
    agl::utl::Parameter<f32> mStartLocationRotY;

    agl::utl::Parameter<sead::SafeString> mStartPosName;
    agl::utl::Parameter<sead::SafeString> mEndPosName;

    agl::utl::Parameter<sead::SafeString> mSkipPolicy;
    agl::utl::Parameter<sead::SafeString> mDispName;
    agl::utl::Parameter<f32> mTraverseLimit;

    agl::utl::Parameter<bool> mVoiceComplete;
    agl::utl::Parameter<bool> mSeComplete;
    agl::utl::Parameter<bool> mBgmComplete;
    agl::utl::Parameter<bool> mEffectComplete;
    agl::utl::Parameter<bool> mEnvComplete;
    agl::utl::Parameter<bool> mFinalComplete;

    agl::utl::Parameter<bool> mForceEnableIK;

    agl::utl::Parameter<bool> mIsUseNakedSound;
    agl::utl::Parameter<sead::SafeString> mWorldMuteType;
    agl::utl::Parameter<sead::SafeString> mBgmStopType;

    agl::utl::Parameter<sead::SafeString> mTraverseType;
    agl::utl::Parameter<sead::Vector3f> mTraversePos;

    agl::utl::Parameter<sead::SafeString> mWaitLoadActorNames;
    agl::utl::Parameter<sead::SafeString> mHideActors;
    agl::utl::Parameter<sead::SafeString> mDisableFarActors;
    agl::utl::Parameter<sead::SafeString> mTraverseMergePolicy;
    agl::utl::Parameter<sead::SafeString> mHighPriorityActors;
    agl::utl::Parameter<sead::Vector3f> mTraverseCutPos;
    agl::utl::Parameter<f32> mTraverseCutRadius;
    agl::utl::Parameter<sead::Vector3f> mTraverseInnerCutPos1;
    agl::utl::Parameter<f32> mTraverseInnerCutRadius1;
    agl::utl::Parameter<sead::Vector3f> mTraverseInnerCutPos2;
    agl::utl::Parameter<f32> mTraverseInnerCutRadius2;
    agl::utl::Parameter<s32> mDisableTraverseTime;
};
KSYS_CHECK_SIZE_NX150(Demo, 0xb20);

}  // namespace ksys::res
