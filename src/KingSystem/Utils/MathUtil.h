#pragma once

#include <math/seadVector.h>

namespace ksys::util {

// too specific for sead
inline float sqXZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    return sead::Mathf::square(a.x - b.x) + sead::Mathf::square(a.z - b.z);
}

}  // namespace ksys::util