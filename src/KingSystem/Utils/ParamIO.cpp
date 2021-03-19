#include "KingSystem/Utils/ParamIO.h"
#include <agl/Utils/aglParameter.h>

namespace ksys {

const char* ParamIO::getString(const agl::utl::ResParameterObj& obj, const char* key,
                               const char* default_value, void*) const {
    const auto param = agl::utl::getResParameter(obj, key);
    if (!param.ptr())
        return default_value;
    return param.getData<const char>();
}

// NON_MATCHING: how the default_value Vec3f is stored on the stack
sead::Vector3f ParamIO::getVec3(const agl::utl::ResParameterObj& obj, const char* key,
                                sead::Vector3f default_value, void*) const {
    const auto param = agl::utl::getResParameter(obj, key);
    return param.ptr() ? *param.getData<sead::Vector3f>() : default_value;
}

}  // namespace ksys
