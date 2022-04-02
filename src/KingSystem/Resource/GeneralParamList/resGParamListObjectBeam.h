#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectBeam : public GParamListObject {
public:
    GParamListObjectBeam();
    const char* getName() const override { return "Beam"; }

    agl::utl::Parameter<s32> mBeamLevel;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectBeam, 0x58);

inline GParamListObjectBeam::GParamListObjectBeam() {
    auto* const obj = &mObj;

    mBeamLevel.init(511, "BeamLevel", "", obj);
}

}  // namespace ksys::res
