#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkpCollidable;

class hkpCollidableCollidableFilter {
public:
    virtual ~hkpCollidableCollidableFilter() = default;

    /// Whether the two objects can collide.
    virtual hkBool isCollisionEnabled(const hkpCollidable& a, const hkpCollidable& b) const = 0;
};
