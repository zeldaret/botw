#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

struct AttPos {
    AttPos();

    void init(agl::utl::IParameterObj* obj, const char* node_key = "Node",
              const char* offset_key = "Offset", const char* rotate_key = "Rotate",
              const char* y_rot_only_key = "YRotOnly");

    // TODO: more functions

    agl::utl::Parameter<sead::SafeString> node;
    agl::utl::Parameter<sead::Vector3f> offset;
    agl::utl::Parameter<sead::Vector3f> rotate;
    agl::utl::Parameter<bool> y_rot_only;
};
KSYS_CHECK_SIZE_NX150(AttPos, 0x98);

}  // namespace ksys::res
