#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectLumberjackTree : public GParamListObject {
public:
    GParamListObjectLumberjackTree();
    const char* getName() const override { return "LumberjackTree"; }

    agl::utl::Parameter<f32> mImpulseThreshold;
    agl::utl::Parameter<bool> mIsValid;
    agl::utl::Parameter<sead::SafeString> mStumpName;
    agl::utl::Parameter<sead::SafeString> mTrunkName;
    agl::utl::Parameter<sead::SafeString> mWeaponWoodName;
    agl::utl::Parameter<sead::SafeString> mBranchName;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectLumberjackTree, 0x118);

inline GParamListObjectLumberjackTree::GParamListObjectLumberjackTree() {
    auto* const obj = &mObj;

    mImpulseThreshold.init(100.0, "ImpulseThreshold", "", obj);
    mIsValid.init(false, "IsValid", "", obj);
    mStumpName.init("", "StumpName", "", obj);
    mTrunkName.init("", "TrunkName", "", obj);
    mWeaponWoodName.init("", "WeaponWoodName", "", obj);
    mBranchName.init("", "BranchName", "", obj);
}

}  // namespace ksys::res
