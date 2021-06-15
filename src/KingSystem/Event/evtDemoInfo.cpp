#include "KingSystem/Event/evtDemoInfo.h"
#include "KingSystem/Resource/Event/resResourceDemo.h"

namespace ksys::evt {

DemoInfo::DemoInfo() {
    init(nullptr);
}

bool DemoInfo::init(const res::Demo* resource) {
    mRes = resource;

    if (mRes) {
        mNoEntryActors.set(mRes->mNoEntryActors.ref());
        mProductFormat.set(mRes->mProductFormat.ref());
        mProgress.set(mRes->mProgress.ref());
        mSaveType.set(mRes->mSaveType.ref());
        mStartType.set(mRes->mStartType.ref());
        mExtension.set(mRes->mExtension.ref());
        mEventMode.set(mRes->mEventMode.ref());
        mStartLocationType.set(mRes->mStartLocationType.ref());
        mTraverseType.set(mRes->mTraverseType.ref());
    } else {
        mNoEntryActors.value = NoEntryActors::kDefault;
        mProductFormat.value = ProductFormat::kOther;
        mProgress.value = Progress::kOther;
        mSaveType.value = SaveType::kNoAutoSave;
        mStartType.value = StartType::kOther;
        mExtension.value = Extension::kOther;
        mEventMode.value = EventMode::kOther;
        mStartLocationType.value = StartLocationType::kOther;
        mTraverseType.value = TraverseType::kOther;
    }

    return mRes != nullptr;
}

const sead::Vector3f& DemoInfo::getLocation() const {
    return isValid() ? mRes->mLocation.ref() : sead::Vector3f::zero;
}

const sead::SafeString& DemoInfo::getMapProjectName() const {
    return isValid() ? mRes->mMapProjectName.ref() : sead::SafeString::cEmptyString;
}

float DemoInfo::getTime() const {
    return isValid() ? mRes->mTime.ref() : -1.0;
}

const sead::SafeString& DemoInfo::getWeather() const {
    return isValid() ? mRes->mWeather.ref() : sead::SafeString::cEmptyString;
}

bool DemoInfo::isStopChemical() const {
    return !mRes || mRes->mIsStopChemical.ref();
}

bool DemoInfo::isWithTransAnimation() const {
    return mRes && mRes->mWithTransAnimation.ref();
}

float DemoInfo::getStartLocationRotY() const {
    return isValid() ? mRes->mStartLocationRotY.ref() : 0.0;
}

const sead::SafeString& DemoInfo::getStartPosName() const {
    return isValid() ? mRes->mStartPosName.ref() : sead::SafeString::cEmptyString;
}

bool DemoInfo::isForbidSkip() const {
    return mRes && mRes->mSkipPolicy.ref() == "Forbid";
}

bool DemoInfo::isSkipPolicyMoveLastFrame() const {
    if (isValid()) {
        if (mRes->mSkipPolicy->include("MoveLastFrame"))
            return true;
    }
    return false;
}

const sead::SafeString& DemoInfo::getDispName() const {
    return isValid() ? mRes->mDispName.ref() : sead::SafeString::cEmptyString;
}

bool DemoInfo::isForceEnableIK() const {
    return mRes && mRes->mForceEnableIK.ref();
}

bool DemoInfo::isUseNakedSound() const {
    return mRes && mRes->mIsUseNakedSound.ref();
}

const sead::SafeString& DemoInfo::getWorldMuteType() const {
    return isValid() ? mRes->mWorldMuteType.ref() : sead::SafeString::cEmptyString;
}

const sead::Vector3f& DemoInfo::getTraversePos() const {
    return isValid() ? mRes->mTraversePos.ref() : sead::Vector3f::zero;
}

const sead::SafeString& DemoInfo::getWaitLoadActorNames() const {
    return isValid() ? mRes->mWaitLoadActorNames.ref() : sead::SafeString::cEmptyString;
}

float DemoInfo::getTraverseLimit() const {
    return isValid() ? mRes->mTraverseLimit.ref() : 0.0;
}

void DemoInfo::NoEntryActors::set(const sead::SafeString& val) {
    if (val == "AllPause")
        value = kAllPause;
    else
        value = kDefault;
}

void DemoInfo::ProductFormat::set(const sead::SafeString& val) {
    if (val == "RealTime")
        value = kRealTime;
    else if (val.startsWith("MovieFile"))
        value = kMovieFile;
    else
        value = kOther;
}

void DemoInfo::Progress::set(const sead::SafeString& val) {
    if (val == "Initialize")
        value = kInitialize;
    else if (val == "Temp")
        value = kTemp;
    else if (val == "Conte")
        value = kConte;
    else if (val == "Animatics")
        value = kAnimatics;
    else if (val == "Product")
        value = kProduct;
    else
        value = kOther;
}

void DemoInfo::SaveType::set(const sead::SafeString& val) {
    if (val == "AutoSave")
        value = kAutoSave;
    else
        value = kNoAutoSave;
}

void DemoInfo::StartType::set(const sead::SafeString& val) {
    if (val == "Seamless")
        value = kSeamless;
    else if (val == "Load")
        value = kLoad;
    else if (val == "Load(NotWaitPlacement)")
        value = kLoadNotWaitPlacement;
    else
        value = kOther;
}

void DemoInfo::Extension::set(const sead::SafeString& val) {
    if (val == "evfl")
        value = kEvfl;
    else if (val == "evtm")
        value = kEvtm;
    else
        value = kOther;
}

void DemoInfo::EventMode::set(const sead::SafeString& val) {
    if (val == "Seamless")
        value = kSeamless;
    else if (val == "Load")
        value = kLoad;
    else if (val == "FullPackage")
        value = kFullPackage;
    else if (val == "Continue")
        value = kContinue;
    else
        value = kOther;
}

void DemoInfo::StartLocationType::set(const sead::SafeString& val) {
    if (val == "Starter")
        value = kStarter;
    else if (val == "StarterPositionOnly")
        value = kStarterPositionOnly;
    else if (val == "Player")
        value = kPlayer;
    else if (val == "SetWorldPos")
        value = kSetWorldPos;
    else if (val == "SearchSafetyPos")
        value = kSearchSafetyPos;
    else if (val == "MapUnitStartPos")
        value = kMapUnitStartPos;
    else
        value = kOther;
}

void DemoInfo::TraverseType::set(const sead::SafeString& val) {
    if (val == "SetPos")
        value = kSetPos;
    else
        value = kDefault;
}

}  // namespace ksys::evt
