#include "KingSystem/Resource/Event/resResourceDemo.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

void Demo::registerFactory(sead::Heap* heap) {
    auto* rm = sead::ResourceMgr::instance();
    if (!rm)
        return;

    if (rm->getDefaultFactory() != rm->findFactory("bdemo"))
        return;

    res::registerEntryFactory(new (heap) EntryFactory<Demo>(1.0, sizeof(Demo)), "bdemo");
}

Demo::Demo() : agl::utl::IParameterIO(".bdemo", 0) {}

void Demo::doCreate_(u8* buffer, u32, sead::Heap*) {
    using FormatStr = sead::FormatFixedSafeString<128>;

    mLocation.init(sead::Vector3f::zero, FormatStr("Location"), "", &mDemoSettingObj);
    mWeather.init(FormatStr("none"), FormatStr("Weather"), "", &mDemoSettingObj);
    mTime.init(-1.0, FormatStr("Time"), "", &mDemoSettingObj);
    mStartType.init(FormatStr("Load"), FormatStr("StartType"), "", &mDemoSettingObj);
    mNoEntryActors.init(FormatStr("none"), FormatStr("NoEntryActors"), "", &mDemoSettingObj);
    mSaveType.init(FormatStr("none"), FormatStr("SaveType"), "", &mDemoSettingObj);
    mExtension.init(FormatStr("evfl"), FormatStr("Extension"), "", &mDemoSettingObj);
    mIsFlashbackDemo.init(false, FormatStr("IsFlashbackDemo"), "", &mDemoSettingObj);

    mOverwritePlayerPos.init(sead::Vector3f::zero, FormatStr("OverwritePlayerPos"), "",
                             &mDemoSettingObj);
    mIsOverwritePlayerPos.init(false, FormatStr("IsOverwritePlayerPos"), "", &mDemoSettingObj);

    mMapProjectName.init("", FormatStr("MapProjectName"), "", &mDemoSettingObj);
    mMapResourceName.init("", FormatStr("MapResourceName"), "", &mDemoSettingObj);
    mIsStartupDemo.init(false, FormatStr("IsStartupDemo"), "", &mDemoSettingObj);
    mProgress.init("", FormatStr("Progress"), "", &mDemoSettingObj);
    mProductFormat.init("", FormatStr("ProductFormat"), "", &mDemoSettingObj);

    mNextDemo.init("", FormatStr("NextDemo"), "", &mDemoSettingObj);

    mIsStopChemical.init(true, FormatStr("IsStopChemical"), "", &mDemoSettingObj);

    mPlayerEndPos.init(sead::Vector3f::zero, FormatStr("PlayerEndPos"), "", &mDemoSettingObj);
    mIsMovePlayerEndPos.init(false, FormatStr("IsMovePlayerEndPos"), "", &mDemoSettingObj);

    mStartLocationType.init(FormatStr("Starter"), FormatStr("StartLocationType"), "",
                            &mDemoSettingObj);
    mEventMode.init(FormatStr("Seamless"), FormatStr("EventMode"), "", &mDemoSettingObj);
    mWithTransAnimation.init(false, FormatStr("WithTransAnimation"), "", &mDemoSettingObj);

    mOverwritePlayerRotY.init(0.0, FormatStr("OverwritePlayerRotY"), "", &mDemoSettingObj);
    mPlayerEndRotY.init(0.0, FormatStr("PlayerEndRotY"), "", &mDemoSettingObj);
    mStartLocationRotY.init(0.0, FormatStr("StartLocationRotY"), "", &mDemoSettingObj);
    mStartPosName.init("", FormatStr("StartPosName"), "", &mDemoSettingObj);
    mEndPosName.init("", FormatStr("EndPosName"), "", &mDemoSettingObj);

    mSkipPolicy.init("Auto", FormatStr("SkipPolicy"), "", &mDemoSettingObj);
    mDispName.init("", FormatStr("DispName"), "", &mDemoSettingObj);
    mTraverseLimit.init(0.0, FormatStr("TraverseLimit"), "", &mDemoSettingObj);

    mForceEnableIK.init(false, FormatStr("ForceEnableIK"), "", &mDemoSettingObj);

    mIsUseNakedSound.init(false, FormatStr("IsUseNakedSound"), "", &mDemoSettingObj);
    mWorldMuteType.init("Thru_ShakeNoise", FormatStr("WorldMuteType"), "", &mDemoSettingObj);
    mBgmStopType.init("StopWithFade", FormatStr("BgmStopType"), "", &mDemoSettingObj);

    mTraverseType.init("", FormatStr("TraverseType"), "", &mDemoSettingObj);
    mTraversePos.init(sead::Vector3f::zero, FormatStr("TraversePos"), "", &mDemoSettingObj);

    mVoiceComplete.init(false, FormatStr("VoiceComplete"), "", &mProgressObj);
    mSeComplete.init(false, FormatStr("SEComplete"), "", &mProgressObj);
    mBgmComplete.init(false, FormatStr("BgmComplete"), "", &mProgressObj);
    mEffectComplete.init(false, FormatStr("EffectComplete"), "", &mProgressObj);
    mEnvComplete.init(false, FormatStr("EnvComplete"), "", &mProgressObj);
    mFinalComplete.init(false, FormatStr("FinalComplete"), "", &mProgressObj);

    mWaitLoadActorNames.init("", FormatStr("WaitLoadActorNames"), "", &mDemoSettingObj);
    mHideActors.init("", FormatStr("HideActors"), "", &mDemoSettingObj);
    mDisableFarActors.init("", FormatStr("DisableFarActors"), "", &mDemoSettingObj);
    mTraverseMergePolicy.init("default", FormatStr("TraverseMergePolicy"), "", &mDemoSettingObj);
    mHighPriorityActors.init("", FormatStr("HighPriorityActors"), "", &mDemoSettingObj);
    mTraverseCutPos.init(sead::Vector3f::zero, FormatStr("TraverseCutPos"), "", &mDemoSettingObj);
    mTraverseCutRadius.init(0.0, FormatStr("TraverseCutRadius"), "", &mDemoSettingObj);
    mTraverseInnerCutPos1.init(sead::Vector3f::zero, FormatStr("TraverseInnerCutPos1"), "",
                               &mDemoSettingObj);
    mTraverseInnerCutRadius1.init(0.0, FormatStr("TraverseInnerCutRadius1"), "", &mDemoSettingObj);
    mTraverseInnerCutPos2.init(sead::Vector3f::zero, FormatStr("TraverseInnerCutPos2"), "",
                               &mDemoSettingObj);
    mTraverseInnerCutRadius2.init(0.0, FormatStr("TraverseInnerCutRadius2"), "", &mDemoSettingObj);
    mDisableTraverseTime.init(-1, FormatStr("DisableTraverseTime"), "", &mDemoSettingObj);

    addObj(&mDemoSettingObj, FormatStr("DemoSetting"));
    addObj(&mProgressObj, FormatStr("Progress"));

    if (buffer)
        applyResParameterArchive(agl::utl::ResParameterArchive{buffer});
}

}  // namespace ksys::res
