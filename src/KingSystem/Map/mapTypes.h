#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>

namespace ksys::map {

using ControlPoints = sead::SafeArray<sead::Vector3f, 2>;

struct SRT {
    sead::Vector3f scale;
    sead::Vector3f rotate;
    sead::Vector3f translate;
};

}  // namespace ksys::map
