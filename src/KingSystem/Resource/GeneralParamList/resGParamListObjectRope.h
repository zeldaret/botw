#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectRope : public GParamListObject {
public:
    GParamListObjectRope();
    const char* getName() const override { return "Rope"; }

    agl::utl::Parameter<bool> mIsAllowCutting;
    agl::utl::Parameter<bool> mIsSetupKeyframed;
    agl::utl::Parameter<f32> mBoneEffectiveLength;
    agl::utl::Parameter<bool> mIsInterpolateEdge;
    agl::utl::Parameter<bool> mIsDeformable;
    agl::utl::Parameter<bool> mIsOneBoneOneShape;
    agl::utl::Parameter<f32> mSplineOffsetRateA;
    agl::utl::Parameter<f32> mSplineOffsetRateB;
    agl::utl::Parameter<f32> mSplineOffsetRateC;
    agl::utl::Parameter<f32> mMtxEndPosOffsetLength;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectRope, 0x178);

inline GParamListObjectRope::GParamListObjectRope() {
    auto* const obj = &mObj;

    mIsAllowCutting.init(true, "IsAllowCutting", "", obj);
    mIsSetupKeyframed.init(false, "IsSetupKeyframed", "", obj);
    mBoneEffectiveLength.init(0.1, "BoneEffectiveLength", "", obj);
    mIsInterpolateEdge.init(true, "IsInterpolateEdge", "", obj);
    mIsDeformable.init(true, "IsDeformable", "", obj);
    mIsOneBoneOneShape.init(false, "IsOneBoneOneShape", "", obj);
    mSplineOffsetRateA.init(0.0, "SplineOffsetRateA", "", obj);
    mSplineOffsetRateB.init(0.0, "SplineOffsetRateB", "", obj);
    mSplineOffsetRateC.init(0.0, "SplineOffsetRateC", "", obj);
    mMtxEndPosOffsetLength.init(0.0, "MtxEndPosOffsetLength", "", obj);
}

}  // namespace ksys::res
