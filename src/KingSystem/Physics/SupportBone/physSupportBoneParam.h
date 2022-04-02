#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterObj.h>
#include <hostio/seadHostIONode.h>

namespace ksys::phys {

struct SupportBoneParam : agl::utl::ParameterObj, sead::hostio::Node {
    SupportBoneParam();

    agl::utl::Parameter<sead::SafeString> support_bone_setup_file_path;
};

}  // namespace ksys::phys
