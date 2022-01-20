#pragma once

#define HK_MATH_H

#include <Havok/Common/Base/Types/hkBaseTypes.h>

#include <Havok/Common/Base/Math/Header/hkMathHeaderConstants.h>
#include <Havok/Common/Base/Math/Matrix/hkMatrix3.h>
#include <Havok/Common/Base/Math/Matrix/hkRotation.h>
#include <Havok/Common/Base/Math/Matrix/hkTransform.h>
#include <Havok/Common/Base/Math/Quaternion/hkQuaternion.h>
#include <Havok/Common/Base/Math/Vector/hkSimdReal.h>
#include <Havok/Common/Base/Math/Vector/hkVector4.h>
#include <Havok/Common/Base/Math/Vector/hkVector4Comparison.h>

#include <Havok/Common/Base/Math/Vector/hkVector4f.inl>

namespace hkMath {

template <typename T1, typename T2>
HK_FORCE_INLINE T1 max2(T1 x, T2 y) {
    return x > static_cast<T1>(y) ? x : static_cast<T1>(y);
}

HK_FORCE_INLINE int hkToIntFast(hkFloat32 r) {
    return int(r);
}

}  // namespace hkMath
