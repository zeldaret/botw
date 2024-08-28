#pragma once

#include <hostio/seadHostIONode.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>

namespace ksys::phys {

struct SupportBoneParam : agl::utl::ParameterObj, sead::hostio::Node {
    SupportBoneParam();

    agl::utl::Parameter<sead::SafeString> support_bone_setup_file_path;
};

}  // namespace ksys::phys
