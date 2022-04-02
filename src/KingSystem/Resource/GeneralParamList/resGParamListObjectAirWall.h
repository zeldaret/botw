#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectAirWall : public GParamListObject {
public:
    GParamListObjectAirWall();
    const char* getName() const override { return "AirWall"; }

    agl::utl::Parameter<sead::SafeString> mLayer;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectAirWall, 0x60);

inline GParamListObjectAirWall::GParamListObjectAirWall() {
    auto* const obj = &mObj;

    mLayer.init("AirWall", "Layer", "", obj);
}

}  // namespace ksys::res
