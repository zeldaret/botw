#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectZora : public GParamListObject {
public:
    GParamListObjectZora();
    const char* getName() const override { return "Zora"; }

    agl::utl::Parameter<f32> mInWaterDepth;
    agl::utl::Parameter<f32> mFloatDepth;
    agl::utl::Parameter<f32> mFloatRadius;
    agl::utl::Parameter<f32> mFloatCycleTime;
    agl::utl::Parameter<f32> mChangeDepthSpeed;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectZora, 0xd8);

inline GParamListObjectZora::GParamListObjectZora() {
    auto* const obj = &mObj;

    mInWaterDepth.init(0.5, "InWaterDepth", "", obj);
    mFloatDepth.init(1.35, "FloatDepth", "", obj);
    mFloatRadius.init(0.02, "FloatRadius", "", obj);
    mFloatCycleTime.init(60.0, "FloatCycleTime", "", obj);
    mChangeDepthSpeed.init(0.066, "ChangeDepthSpeed", "", obj);
}

}  // namespace ksys::res
