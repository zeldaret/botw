#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectCamera : public GParamListObject {
public:
    GParamListObjectCamera();
    const char* getName() const override { return "Camera"; }

    agl::utl::Parameter<f32> mDefaultConnectScaleAfterEvent;
    agl::utl::Parameter<f32> mLatConnectRateAfterEvent;
    agl::utl::Parameter<f32> mLngConnectRateAfterEvent;
    agl::utl::Parameter<f32> mDistConnectRateAfterEvent;
    agl::utl::Parameter<f32> mFovyConnectRateAfterEvent;
    agl::utl::Parameter<f32> mConnectAfterEventMin;
    agl::utl::Parameter<f32> mConnectAfterEventMax;
    agl::utl::Parameter<f32> mRoofGradientNearHighWeight;
    agl::utl::Parameter<f32> mRoofGradientFarHighWeight;
    agl::utl::Parameter<f32> mRoofGradientNearLowWeight;
    agl::utl::Parameter<f32> mRoofGradientFarLowWeight;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectCamera, 0x198);

inline GParamListObjectCamera::GParamListObjectCamera() {
    auto* const obj = &mObj;

    mDefaultConnectScaleAfterEvent.init(1.0, "DefaultConnectScaleAfterEvent", "", obj);
    mLatConnectRateAfterEvent.init(1.5, "LatConnectRateAfterEvent", "", obj);
    mLngConnectRateAfterEvent.init(0.75, "LngConnectRateAfterEvent", "", obj);
    mDistConnectRateAfterEvent.init(3.0, "DistConnectRateAfterEvent", "", obj);
    mFovyConnectRateAfterEvent.init(0.0, "FovyConnectRateAfterEvent", "", obj);
    mConnectAfterEventMin.init(30.0, "ConnectAfterEventMin", "", obj);
    mConnectAfterEventMax.init(1000.0, "ConnectAfterEventMax", "", obj);
    mRoofGradientNearHighWeight.init(0.0, "RoofGradientNearHighWeight", "", obj);
    mRoofGradientFarHighWeight.init(0.0, "RoofGradientFarHighWeight", "", obj);
    mRoofGradientNearLowWeight.init(0.0, "RoofGradientNearLowWeight", "", obj);
    mRoofGradientFarLowWeight.init(0.0, "RoofGradientFarLowWeight", "", obj);
}

}  // namespace ksys::res
