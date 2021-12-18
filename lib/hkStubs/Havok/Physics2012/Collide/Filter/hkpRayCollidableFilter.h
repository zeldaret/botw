#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkpWorldRayCastInput;
class hkpCollidable;

class hkpRayCollidableFilter {
public:
    virtual ~hkpRayCollidableFilter() = default;

    virtual hkBool isCollisionEnabled(const hkpWorldRayCastInput& a,
                                      const hkpCollidable& collidableB) const = 0;
};
