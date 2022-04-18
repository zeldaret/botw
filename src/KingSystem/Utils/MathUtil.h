#pragma once

#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
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

inline void lerp(sead::Vector3f* result, const sead::Vector3f& a, const sead::Vector3f& b,
                 float t) {
    result->x = a.x + (b.x - a.x) * t;
    result->y = a.y + (b.y - a.y) * t;
    result->z = a.z + (b.z - a.z) * t;
}

inline sead::Vector3f lerp(const sead::Vector3f& a, const sead::Vector3f& b, float t) {
    sead::Vector3f result;
    lerp(&result, a, b, t);
    return result;
}

inline bool isVectorInvalid(const sead::Vector3f& vec) {
    for (int i = 0; i < 3; ++i) {
        if (std::isnan(vec.e[i]))
            return true;
    }
    return false;
}

inline bool isMatrixInvalid(const sead::Matrix34f& matrix) {
    for (float x : matrix.a) {
        if (std::isnan(x))
            return true;
    }
    return false;
}

}  // namespace ksys::util
