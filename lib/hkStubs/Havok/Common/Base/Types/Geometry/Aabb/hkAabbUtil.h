#pragma once

#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>

namespace hkAabbUtil {

void calcAabb(const hkTransform& localToWorld, const hkVector4& halfExtents,
              hkSimdRealParameter extraRadius, hkAabb& aabbOut);

inline void calcAabb(const hkTransform& localToWorld, const hkVector4& halfExtents,
                     hkSimdRealParameter extraRadius, hkAabb& aabbOut) {
    hkVector4 x, y, z;
    x.setMul(halfExtents.getComponent<0>(), localToWorld.getRotation().getColumn<0>());
    y.setMul(halfExtents.getComponent<1>(), localToWorld.getRotation().getColumn<1>());
    z.setMul(halfExtents.getComponent<2>(), localToWorld.getRotation().getColumn<2>());

    x.setAbs(x);
    y.setAbs(y);
    z.setAbs(z);

    hkVector4 max;
    z.setAdd(z, extraRadius);
    max.setAdd(x, y);
    max.add(z);

    hkVector4 min;
    min.setNeg<4>(max);

    max.add(localToWorld.getTranslation());
    min.add(localToWorld.getTranslation());

    aabbOut.m_max = max;
    aabbOut.m_min = min;
}

}  // namespace hkAabbUtil
