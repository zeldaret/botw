#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectWeaponThrow : public GParamListObject {
public:
    GParamListObjectWeaponThrow();
    const char* getName() const override { return "WeaponThrow"; }

    agl::utl::Parameter<f32> mThrowSpeed;
    agl::utl::Parameter<f32> mThrowRotSpeed;
    agl::utl::Parameter<f32> mThrowDist;
    agl::utl::Parameter<sead::Vector3f> mThrowRigidBodyBaseAxis;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectWeaponThrow, 0xc0);

inline GParamListObjectWeaponThrow::GParamListObjectWeaponThrow() {
    auto* const obj = &mObj;

    mThrowSpeed.init(1.0, "ThrowSpeed", "", obj);
    mThrowRotSpeed.init(50.0, "ThrowRotSpeed", "", obj);
    mThrowDist.init(5.0, "ThrowDist", "", obj);
    mThrowRigidBodyBaseAxis.init({0.0, 0.0, 1.0}, "ThrowRigidBodyBaseAxis", "", obj);
}

}  // namespace ksys::res
