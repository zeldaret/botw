#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectLiftable : public GParamListObject {
public:
    GParamListObjectLiftable();
    const char* getName() const override { return "Liftable"; }

    agl::utl::Parameter<sead::SafeString> mLiftType;
    agl::utl::Parameter<s32> mThrownMass;
    agl::utl::Parameter<sead::Vector3f> mThrownRotSpd;
    agl::utl::Parameter<sead::Vector3f> mLiftPosOffset;
    agl::utl::Parameter<sead::Vector3f> mLiftRotOffset;
    agl::utl::Parameter<s32> mLiftRotFrame;
    agl::utl::Parameter<sead::SafeString> mAddLiftRotOffsetList;
    agl::utl::Parameter<bool> mChaseLiftRotOffset;
    agl::utl::Parameter<sead::Vector3f> mLiftCenterOffset;
    agl::utl::Parameter<sead::Vector3f> mPutPosOffset;
    agl::utl::Parameter<sead::Vector3f> mPutRotOffset;
    agl::utl::Parameter<s32> mPutRotFrame;
    agl::utl::Parameter<sead::SafeString> mAddPutRotOffsetList;
    agl::utl::Parameter<bool> mIsUpdateOffsetEachFrame;
    agl::utl::Parameter<bool> mIsUse2MassConstraintMode;
    agl::utl::Parameter<bool> mIsSetChemicalParent;
    agl::utl::Parameter<bool> mDisableFreezeLift;
    agl::utl::Parameter<bool> mDisableBurnLift;
    agl::utl::Parameter<s32> mThrowReactionLevel;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectLiftable, 0x2e0);

inline GParamListObjectLiftable::GParamListObjectLiftable() {
    auto* const obj = &mObj;

    mLiftType.init("", "LiftType", "", obj);
    mThrownMass.init(10, "ThrownMass", "", obj);
    mThrownRotSpd.init({0.0, 0.0, 0.0}, "ThrownRotSpd", "", obj);
    mLiftPosOffset.init({0.0, 0.0, 0.0}, "LiftPosOffset", "", obj);
    mLiftRotOffset.init({0.0, 0.0, 0.0}, "LiftRotOffset", "", obj);
    mLiftRotFrame.init(10, "LiftRotFrame", "", obj);
    mAddLiftRotOffsetList.init("", "AddLiftRotOffsetList", "", obj);
    mChaseLiftRotOffset.init(false, "ChaseLiftRotOffset", "", obj);
    mLiftCenterOffset.init({0.0, 0.0, 0.0}, "LiftCenterOffset", "", obj);
    mPutPosOffset.init({0.0, 0.0, 0.5}, "PutPosOffset", "", obj);
    mPutRotOffset.init({0.0, 0.0, 0.0}, "PutRotOffset", "", obj);
    mPutRotFrame.init(10, "PutRotFrame", "", obj);
    mAddPutRotOffsetList.init("", "AddPutRotOffsetList", "", obj);
    mIsUpdateOffsetEachFrame.init(false, "IsUpdateOffsetEachFrame", "", obj);
    mIsUse2MassConstraintMode.init(true, "IsUse2MassConstraintMode", "", obj);
    mIsSetChemicalParent.init(true, "IsSetChemicalParent", "", obj);
    mDisableFreezeLift.init(false, "DisableFreezeLift", "", obj);
    mDisableBurnLift.init(false, "DisableBurnLift", "", obj);
    mThrowReactionLevel.init(-1, "ThrowReactionLevel", "", obj);
}

}  // namespace ksys::res
