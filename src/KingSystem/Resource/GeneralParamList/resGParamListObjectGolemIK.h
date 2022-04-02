#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectGolemIK : public GParamListObject {
public:
    GParamListObjectGolemIK();
    const char* getName() const override { return "GolemIK"; }

    agl::utl::Parameter<f32> mFootRayCheckDist;
    agl::utl::Parameter<f32> mFootDownRatio;
    agl::utl::Parameter<f32> mFootUpRatio;
    agl::utl::Parameter<f32> mKneeExtendL;
    agl::utl::Parameter<f32> mKneeShrinkL;
    agl::utl::Parameter<f32> mFootExtendL;
    agl::utl::Parameter<f32> mFootShrinkL;
    agl::utl::Parameter<f32> mKneeExtendR;
    agl::utl::Parameter<f32> mKneeShrinkR;
    agl::utl::Parameter<f32> mFootExtendR;
    agl::utl::Parameter<f32> mFootShrinkR;
    agl::utl::Parameter<f32> mArmRayCheckDist;
    agl::utl::Parameter<f32> mArmDownRatio;
    agl::utl::Parameter<f32> mArmUpRatio;
    agl::utl::Parameter<f32> mElbowExtendL;
    agl::utl::Parameter<f32> mElbowShrinkL;
    agl::utl::Parameter<f32> mWristExtendL;
    agl::utl::Parameter<f32> mWristShrinkL;
    agl::utl::Parameter<f32> mElbowExtendR;
    agl::utl::Parameter<f32> mElbowShrinkR;
    agl::utl::Parameter<f32> mWristExtendR;
    agl::utl::Parameter<f32> mWristShrinkR;
    agl::utl::Parameter<f32> mWaistRotateRatio;
    agl::utl::Parameter<f32> mWaistMorphRatio;
    agl::utl::Parameter<f32> mWaistResetMorphRatio;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectGolemIK, 0x358);

inline GParamListObjectGolemIK::GParamListObjectGolemIK() {
    auto* const obj = &mObj;

    mFootRayCheckDist.init(3.0, "FootRayCheckDist", "", obj);
    mFootDownRatio.init(0.2, "FootDownRatio", "", obj);
    mFootUpRatio.init(0.1, "FootUpRatio", "", obj);
    mKneeExtendL.init(0.5, "KneeExtendL", "", obj);
    mKneeShrinkL.init(0.5, "KneeShrinkL", "", obj);
    mFootExtendL.init(0.5, "FootExtendL", "", obj);
    mFootShrinkL.init(0.5, "FootShrinkL", "", obj);
    mKneeExtendR.init(0.5, "KneeExtendR", "", obj);
    mKneeShrinkR.init(0.5, "KneeShrinkR", "", obj);
    mFootExtendR.init(0.5, "FootExtendR", "", obj);
    mFootShrinkR.init(0.5, "FootShrinkR", "", obj);
    mArmRayCheckDist.init(3.0, "ArmRayCheckDist", "", obj);
    mArmDownRatio.init(0.05, "ArmDownRatio", "", obj);
    mArmUpRatio.init(0.05, "ArmUpRatio", "", obj);
    mElbowExtendL.init(0.5, "ElbowExtendL", "", obj);
    mElbowShrinkL.init(0.5, "ElbowShrinkL", "", obj);
    mWristExtendL.init(0.5, "WristExtendL", "", obj);
    mWristShrinkL.init(0.5, "WristShrinkL", "", obj);
    mElbowExtendR.init(0.5, "ElbowExtendR", "", obj);
    mElbowShrinkR.init(0.5, "ElbowShrinkR", "", obj);
    mWristExtendR.init(0.5, "WristExtendR", "", obj);
    mWristShrinkR.init(0.5, "WristShrinkR", "", obj);
    mWaistRotateRatio.init(0.5, "WaistRotateRatio", "", obj);
    mWaistMorphRatio.init(0.2, "WaistMorphRatio", "", obj);
    mWaistResetMorphRatio.init(0.1, "WaistResetMorphRatio", "", obj);
}

}  // namespace ksys::res
