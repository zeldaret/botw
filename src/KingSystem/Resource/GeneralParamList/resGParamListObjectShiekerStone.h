#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectShiekerStone : public GParamListObject {
public:
    GParamListObjectShiekerStone();
    const char* getName() const override { return "ShiekerStone"; }

    agl::utl::Parameter<sead::SafeString> mNodeNameWithWaist;
    agl::utl::Parameter<sead::Vector3f> mTransOffsetWithWaist;
    agl::utl::Parameter<sead::Vector3f> mRotOffsetWithWaist;
    agl::utl::Parameter<sead::SafeString> mNodeNameWithHand;
    agl::utl::Parameter<sead::Vector3f> mTransOffsetWithHand;
    agl::utl::Parameter<sead::Vector3f> mRotOffsetWithHand;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectShiekerStone, 0x128);

inline GParamListObjectShiekerStone::GParamListObjectShiekerStone() {
    auto* const obj = &mObj;

    mNodeNameWithWaist.init("Pod_C", "NodeNameWithWaist", "", obj);
    mTransOffsetWithWaist.init({0.125, 0.0, -0.017}, "TransOffsetWithWaist", "", obj);
    mRotOffsetWithWaist.init({2.0, 184.0, -3.0}, "RotOffsetWithWaist", "", obj);
    mNodeNameWithHand.init("Weapon_L", "NodeNameWithHand", "", obj);
    mTransOffsetWithHand.init({0.0, 0.0, 0.0}, "TransOffsetWithHand", "", obj);
    mRotOffsetWithHand.init({180.0, 180.0, 0.0}, "RotOffsetWithHand", "", obj);
}

}  // namespace ksys::res
