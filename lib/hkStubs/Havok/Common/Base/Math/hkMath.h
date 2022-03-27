#pragma once

#define HK_MATH_H

// Note: these headers have to be included in a specific order.
// clang-format off

#include <Havok/Common/Base/Types/hkBaseTypes.h>
#include <Havok/Common/Base/Math/Header/hkMathHeaderConstants.h>

// Forward declarations
class hkVector4f;
class hkVector4fComparison;
class hkSimdFloat32;
class hkQuaternionf;
class hkMatrix3f;
class hkRotationf;
class hkTransformf;
class hkQTransformf;
class hkQsTransformf;
class hkMatrix4f;

// Type aliases
using hkVector4fParameter = const hkVector4f&;
using hkVector4fComparisonParameter = const hkVector4fComparison&;
using hkSimdFloat32Parameter = const hkSimdFloat32&;
using hkQuaternionfParameter = const hkQuaternionf&;

// Headers
#include <Havok/Common/Base/Math/Vector/hkVector4.h>
#include <Havok/Common/Base/Math/Vector/hkVector4Comparison.h>
#include <Havok/Common/Base/Math/Vector/hkSimdReal.h>
#include <Havok/Common/Base/Math/Quaternion/hkQuaternion.h>
#include <Havok/Common/Base/Math/Matrix/hkMatrix3.h>
#include <Havok/Common/Base/Math/Matrix/hkRotation.h>
#include <Havok/Common/Base/Math/Matrix/hkTransform.h>
#include <Havok/Common/Base/Math/QsTransform/hkQsTransform.h>
#include <Havok/Common/Base/Math/Matrix/hkMatrix4.h>

// Implementations
#include <Havok/Common/Base/Math/Vector/hkVector4f.inl>
#include <Havok/Common/Base/Math/Vector/hkVector4fComparison.inl>
#include <Havok/Common/Base/Math/Quaternion/hkQuaternionf.inl>
#include <Havok/Common/Base/Math/Matrix/hkMatrix3f.inl>
#include <Havok/Common/Base/Math/QsTransform/hkQsTransformf.inl>

// clang-format on

namespace hkMath {

template <typename T1, typename T2>
HK_FORCE_INLINE T1 max2(T1 x, T2 y) {
    return x > static_cast<T1>(y) ? x : static_cast<T1>(y);
}

HK_FORCE_INLINE int hkToIntFast(hkFloat32 r) {
    return int(r);
}

HK_FORCE_INLINE hkBool32 intInRange(int value, int lowInclusive, int highExclusive) {
    return (lowInclusive <= value) & (value < highExclusive);
}

}  // namespace hkMath
