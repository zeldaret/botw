#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::chm {

class Rigid : public agl::utl::IParameterObj {
public:
    Rigid();

    u32 getAttribute() const { return attribute.ref(); }
    const sead::SafeString& getRigidSetName() const { return rigid_set_name.ref(); }
    const sead::SafeString& getRigidName() const { return rigid_name.ref(); }
    float getVolume() const { return volume.ref(); }
    float getMass() const { return mass.ref(); }
    float getBurnOutTime() const { return burn_out_time.ref(); }

private:
    agl::utl::Parameter<u32> attribute;
    agl::utl::Parameter<sead::FixedSafeString<64>> rigid_set_name;
    agl::utl::Parameter<sead::FixedSafeString<64>> rigid_name;
    agl::utl::Parameter<float> volume;
    agl::utl::Parameter<float> mass;
    agl::utl::Parameter<float> burn_out_time;
};
KSYS_CHECK_SIZE_NX150(Rigid, 0x190);

}  // namespace ksys::chm
