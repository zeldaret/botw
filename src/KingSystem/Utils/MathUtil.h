#pragma once

#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>

namespace ksys::util {

/// Remap `value` from a [low, high] range to [new_low, new_high].
inline float remapRange(float value, float low, float high, float new_low, float new_high) {
    return new_low + (value - low) * (new_high - new_low) / (high - low);
}

/// Clamp `value` to [low, high] and then remap the value to the range [new_low, new_high].
inline float clampAndRemapRange(float value, float low, float high, float new_low, float new_high) {
    value = sead::Mathf::clamp(value, low, high);
    return remapRange(value, low, high, new_low, new_high);
}

// too specific for sead
inline float sqXZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    return sead::Mathf::square(a.x - b.x) + sead::Mathf::square(a.z - b.z);
}

inline float dot(sead::Vector3f u, const sead::Matrix34f& mtx, int row) {
    return u.x * mtx(row, 0) + u.y * mtx(row, 1) + u.z * mtx(row, 2);
}

}  // namespace ksys::util
